#include "stdafx.h"
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <fstream>
#include <boost/thread/thread.hpp>
#ifdef _WIN32
	#pragma warning (disable : 4251)
	#pragma warning (disable : 4098)
#endif
#define CPPCONN_DONT_TYPEDEF_MS_TYPES_TO_C99_TYPES
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "Camera.h"
#include "Detector.h"

#define EVER ;;
#ifdef _WIN32
	#define __FILE_SHORT__ \
		(strrchr(__FILE__,'\\') \
		 ? strrchr(__FILE__,'\\')+1 \
		 : __FILE__ \
		)
#else
	#define __FILE_SHORT__ \
		(strrchr(__FILE__,'/') \
		 ? strrchr(__FILE__,'/')+1 \
		 : __FILE__ \
		)
#endif

using namespace std;
using namespace sql;

Driver *driver;
unique_ptr<Connection> con;
unique_ptr<Statement> stmt;

class Crawler
{
public:
	unique_ptr<ResultSet> camera_results;

	Crawler(unsigned int parking_id)
	{
		unique_ptr<PreparedStatement> query(con->prepareStatement("SELECT id, address, type, threshold_high, threshold_low, threshold_scan, scale FROM camera WHERE parking_id = ?"));
		query->setInt(1, parking_id);

		camera_results.reset(query->executeQuery());
	}

	bool hasNext()
	{
		return camera_results->next();
	}

	vector<Spot *> * loadSpots()
	{
		unique_ptr<PreparedStatement> query(con->prepareStatement("SELECT id, status, p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y FROM spot WHERE camera_id = ?"));
		query->setInt(1, camera_results->getInt("id"));
		unique_ptr<ResultSet> res(query->executeQuery());

		vector<Spot *> *spots = new vector<Spot *>;

		while (res->next())
		{
			auto *spot = new Spot;
			spot->id = res->getInt("id");
			spot->resetStatus(res->getInt("status"));
			spot->corners[0].x = res->getInt("p1x");
			spot->corners[0].y = res->getInt("p1y");
			spot->corners[1].x = res->getInt("p2x");
			spot->corners[1].y = res->getInt("p2y");
			spot->corners[2].x = res->getInt("p3x");
			spot->corners[2].y = res->getInt("p3y");
			spot->corners[3].x = res->getInt("p4x");
			spot->corners[3].y = res->getInt("p4y");

			spots->push_back(spot);
		}

		return spots;
	}
};

unsigned int get_last_insert_id(string table)
{
	unique_ptr<PreparedStatement> query(con->prepareStatement("SELECT LAST_INSERT_ID() FROM " + table)); 
	unique_ptr<ResultSet> insert_res(query->executeQuery());
	insert_res->first();
	return insert_res->getUInt(1);
}


struct Conf {
	SQLString host;
	SQLString username;
	SQLString password;
	SQLString schema;
	boost::posix_time::time_duration no_rows_sleep;
	unsigned int scan_interval;
	bool display_grid;

	Conf()
		: host("tcp://127.0.0.1:3306"), 
		  username("root"),
		  password(""),
		  schema("parking"),
		  no_rows_sleep(0, 0, 1),
		  scan_interval(30),
		  display_grid(false)
	{}
};


int main(int argc, char *argv[])
{
	Conf conf;

	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];
		
		if (arg == "-h")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -h [host]\n");
				return EXIT_FAILURE;
			}

			conf.host = argv[++i];
		}
		else if (arg == "-u")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -u [username]\n");
				return EXIT_FAILURE;
			}

			conf.username = argv[++i];
		}
		else if (arg == "-p")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -p [password]\n");
				return EXIT_FAILURE;
			}

			conf.password = argv[++i];
		}
		else if (arg == "-s")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -p [schema]\n");
				return EXIT_FAILURE;
			}

			conf.schema = argv[++i];
		}
		else if (arg == "-t")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -t [no rows sleep in seconds]\n");
				return EXIT_FAILURE;
			}

			conf.no_rows_sleep = boost::posix_time::time_duration(0, 0, atol(argv[++i]));
		}
		else if (arg == "-i")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -t [scan interval in seconds]\n");
				return EXIT_FAILURE;
			}

			conf.scan_interval = atoi(argv[++i]);
		}
		else if (arg == "-g")
		{
			conf.display_grid = true;
		}
	}

	try
	{
		printf("Connecting to database...\n");

		driver = get_driver_instance();

		con.reset(driver->connect(conf.host, conf.username, conf.password));
		con->setSchema(conf.schema);

		printf("Connected.\n");

		stmt.reset(con->createStatement());

		for (EVER)
		{
			unique_ptr<PreparedStatement> query(con->prepareStatement("SELECT id FROM parking WHERE last_scan <= ? ORDER BY last_scan ASC LIMIT 1"));
			query->setUInt(1, (unsigned int) time(nullptr) - conf.scan_interval);

			unique_ptr<ResultSet> res(query->executeQuery());

			if ( ! res->first())
			{
				printf("No data, skipping.\n");
				boost::this_thread::sleep(conf.no_rows_sleep);
				continue;
			}

			unsigned int parking_id = res->getUInt("id");
			printf("Scanning parking (id %u)\n", parking_id);

			// insert basic parking stats
			unsigned int free_spots = 0;
			query.reset(con->prepareStatement("INSERT INTO stats_parking (parking_id) VALUES(?)")); 
			query->setUInt(1, parking_id);
			query->executeUpdate();
			unsigned int stats_parking_id = get_last_insert_id("stats_parking");

			Crawler crawler(parking_id);

			while (crawler.hasNext())
			{
				unsigned int camera_id = crawler.camera_results->getUInt("id");
				string type = crawler.camera_results->getString("type");
				string address = crawler.camera_results->getString("address");
				double threshold_high = crawler.camera_results->getDouble("threshold_high");
				double threshold_low = crawler.camera_results->getDouble("threshold_low");
				double threshold_scan = crawler.camera_results->getDouble("threshold_scan");
				double scale = crawler.camera_results->getDouble("scale");

				unique_ptr<CameraDriver> camera(CameraDriver::factory(type, address));

				if ( ! camera->isValid())
				{
					printf("    Warning: Failed to retrive image from camera (id %u); skipping\n", camera_id);
					continue;
				}

				Detector detector;
				clock_t start, end;

				start = clock();
				if ( ! detector.loadImage(camera->getImagePath(), threshold_low, threshold_high, scale))
				{
					printf("    Warning: Failed to load image from camera (id %u) into detector; skipping\n", camera_id);
					continue;
				}

				unique_ptr<vector<Spot *>> spots(crawler.loadSpots());

				detector.findFreeSpots(*spots, threshold_scan);
				end = clock();

				#ifdef _DEBUG
					printf("    Info: scanned %u spots in %u microseconds\n", spots->size(), (end - start) * 1000 / CLOCKS_PER_SEC);
				#endif

				unsigned int to_update = 0;
				unsigned int camera_free_spots = 0;
				vector<int> update_to_free_ids, update_to_occupied_ids;
				stringstream insert_spot_stats;

				// insert camera and spots stats
				query.reset(con->prepareStatement("INSERT INTO stats_camera (camera_id, stats_parking_id) VALUES(?, ?)")); 
				query->setUInt(1, camera_id);
				query->setUInt(2, stats_parking_id);
				query->executeUpdate();
				unsigned int stats_camera_id = get_last_insert_id("stats_camera");

				insert_spot_stats << "INSERT INTO stats_spot (spot_id, stats_camera_id, status) VALUES ";

				for (size_t i = 0, l = spots->size(); i < l; i++)
				{
					Spot &spot = *(*spots)[i];
					if (spot.status != spot.original_status)
					{
						to_update++;

						switch (spot.status)
						{
						case Free:
							update_to_free_ids.push_back(spot.id);
							break;
						case Occupied:
							update_to_occupied_ids.push_back(spot.id);
							break;
						}
					}

					insert_spot_stats << "(" << spot.id << "," << stats_camera_id << ",";
					switch (spot.status)
					{
					case Free:
						free_spots++;
						camera_free_spots++;
						insert_spot_stats << "'free'),";
						break;
					case Occupied:
						insert_spot_stats << "'occupied'),";
						break;
					case Blocked:
						insert_spot_stats << "'blocked'),";
						break;
					}
				}


				// insert spots stats
				if (spots->size() > 0)
				{
					string insert_query = insert_spot_stats.str();
					query.reset(con->prepareStatement(insert_query.substr(0, insert_query.length() - 1)));
					query->executeUpdate();
				}

				// update camera stats
				query.reset(con->prepareStatement("UPDATE stats_camera SET free_spots = ? WHERE id = ?"));
				query->setUInt(1, camera_free_spots);
				query->setUInt(2, stats_camera_id);
				query->executeUpdate();

				#ifdef _DEBUG
					printf("    Info: updating %i spots\n", to_update);
				#endif

				if (conf.display_grid)
				{
					detector.displayGrid(*spots);
					boost::this_thread::sleep(conf.no_rows_sleep);
				}

				size_t lf = update_to_free_ids.size();
				size_t lo = update_to_occupied_ids.size();

				if (lf > 0)
				{
					stringstream update_to_free;

					update_to_free << "UPDATE spot SET status = 1 WHERE id IN (";
					
					lf -= 1;
					for (size_t i = 0; i < lf; i++)
					{
						update_to_free << update_to_free_ids[i] << ",";
					}

					update_to_free << update_to_free_ids[lf] << ")";

					query.reset(con->prepareStatement(update_to_free.str()));
					query->executeUpdate();
				}

				if (lo > 0)
				{
					stringstream update_to_occupied;
					
					update_to_occupied << "UPDATE spot SET status = 2 WHERE id IN (";

					lo -= 1;
					for (size_t i = 0; i < lo; i++)
					{
						update_to_occupied << update_to_occupied_ids[i] << ",";
					}

					update_to_occupied << update_to_occupied_ids[lo] << ")";
					
					query.reset(con->prepareStatement(update_to_occupied.str()));
					query->executeUpdate();
				}

				for (size_t i = 0, l = spots->size(); i < l; i++)
				{
					delete spots->at(i);
				}

			}

			query.reset(con->prepareStatement("UPDATE parking SET last_scan = ? WHERE id = ?"));
			query->setUInt(1, (unsigned int) time(nullptr));
			query->setUInt(2, parking_id);
			query->executeUpdate();

			// update parkign stats
			query.reset(con->prepareStatement("UPDATE stats_parking SET free_spots = ? WHERE id = ?"));
			query->setUInt(1, free_spots);
			query->setUInt(2, stats_parking_id);
			query->executeUpdate();
		}
	}
	catch (SQLException &e)
	{
		printf("Error: SQLException in %s\n%s\n(MySQL error code: %i, SQLState: %s)\n",
				__FILE_SHORT__, e.what(), e.getErrorCode(), e.getSQLState().c_str());
	}
	catch (exception &e)
	{
		printf("Error: Exception in %s\n%s\n",
				__FILE_SHORT__,  e.what());
	}
	catch (...)
	{
		printf("Error: Unknown exception in %s\n",
				__FILE_SHORT__);
	}

	system("pause");
	return EXIT_SUCCESS;
}