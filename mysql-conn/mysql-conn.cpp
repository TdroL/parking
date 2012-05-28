// mysql-conn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <boost/thread/thread.hpp>
#ifdef _WIN32
	#pragma warning (disable : 4251)
#endif
#define CPPCONN_DONT_TYPEDEF_MS_TYPES_TO_C99_TYPES
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

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

int main(int argc, _TCHAR* argv[])
{
	string dns = "tcp://127.0.0.1:3306";
	SQLString username = "root";
	SQLString password = "";
	SQLString schema = "parking";
	const boost::posix_time::seconds noRowsDelay(1);

	Driver *driver;
	unique_ptr<Connection> con;
	unique_ptr<Statement> stmt;
	unique_ptr<ResultSet> res;
	unique_ptr<PreparedStatement> stat_camera;
	unique_ptr<PreparedStatement> stat_spot;

	try
	{
		printf("Connecting to database...\n");

		driver = get_driver_instance();

		con.reset(driver->connect(dns, username, password));
		con->setSchema(schema);

		printf("Connected.\n");

		stmt.reset(con->createStatement());

		stat_camera.reset(con->prepareStatement("SELECT id, address, type, threshold_high, threshold_low, threshold_scan FROM camera ORDER BY last_scan ASC LIMIT 1"));

		for(;;)
		{
			res.reset(stat_camera->executeQuery());

			if ( ! res->first())
			{
				printf("No data, skipping.\n");
				boost::this_thread::sleep(noRowsDelay);
				continue;
			}

			printf("Scanning [id: %u]\n", res->getInt("id"));
			
			string address = res->getString("address");
			string type = res->getString("type");

			stat_spot.reset(con->prepareStatement("SELECT id, p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y FROM spot WHERE camera_id = ?"));
			stat_spot->setInt(1, res->getInt("id"));

			res.reset(stat_spot->executeQuery());

			struct Point
			{
				unsigned int x, y;
			};

			struct Spot
			{
				unsigned int id;
				Point p1;
				Point p2;
				Point p3;
				Point p4;
			};

			vector<Spot *> spots;

			while (res->next())
			{
				Spot *spot = new Spot;
				spot->id = res->getInt("id");
				spot->p1.x = res->getInt("p1x");
				spot->p1.y = res->getInt("p1y");
				spot->p2.x = res->getInt("p2x");
				spot->p2.y = res->getInt("p2y");
				spot->p3.x = res->getInt("p3x");
				spot->p3.y = res->getInt("p3y");
				spot->p4.x = res->getInt("p4x");
				spot->p4.y = res->getInt("p4y");

				spots.push_back(spot);
			}

			printf("Loaded %u spots\n", spots.size());

			for each (Spot *spot in spots)
			{
				delete spot;
			}
		}
	}
	catch (SQLException &e)
	{
		printf("Error: SQLException in %s (%s) on line %u\n%s\n(MySQL error code: %i, SQLState: %s)\n",
				__FILE_SHORT__, __FUNCTION__, __LINE__, e.what(), e.getErrorCode(), e.getSQLState().c_str());

		system("pause");
	}
	catch (exception &e)
	{
		printf("Error: Exception in %s (%s) on line %u\n%s\n",
				__FILE_SHORT__, __FUNCTION__, __LINE__, e.what());

		system("pause");
	}
	catch (...)
	{
		printf("Error: Unknown exception in %s (%s) on line %u\n",
				__FILE_SHORT__, __FUNCTION__, __LINE__);

		system("pause");
	}

	return EXIT_SUCCESS;
}

