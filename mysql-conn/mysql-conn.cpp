// mysql-conn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <sstream>
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
	string dns = "tcp://127.0.0.1:3307";
	SQLString username = "root";
	SQLString password = "";
	SQLString schema = "parking";
	const boost::posix_time::seconds noRowsDelay(1);

	Driver *driver;
	unique_ptr<Connection> con;
	unique_ptr<Statement> stmt;
	unique_ptr<ResultSet> res;
	unique_ptr<PreparedStatement> pstmt;

	try
	{
		printf("Connecting to database...\n");

		driver = get_driver_instance();

		con.reset(driver->connect(dns, username, password));
		con->setSchema(schema);

		printf("Connected.\n");

		stmt.reset(con->createStatement());

		pstmt.reset(con->prepareStatement("SELECT id, adres, typ FROM parking ORDER BY last_check ASC LIMIT 1"));

		for(;;)
		{
			res.reset(pstmt->executeQuery());

			if ( ! res->first())
			{
				printf("No data, skipping.\n");
				boost::this_thread::sleep(noRowsDelay);
			}

			while (res->next())
			printf("\t... MySQL counts: %u\n", res->getInt("id"));
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

