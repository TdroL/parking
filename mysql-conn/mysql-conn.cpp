// mysql-conn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <sstream>
#define CPPCONN_DONT_TYPEDEF_MS_TYPES_TO_C99_TYPES
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

int main(int argc, _TCHAR* argv[])
{
	string dns = "tcp://127.0.0.1:3306";
	SQLString username = "root";
	SQLString password = "";
	SQLString schema = "parking";

	Driver *driver;
	unique_ptr<Connection> con;
	unique_ptr<Statement> stmt;
	unique_ptr<ResultSet> res;
	unique_ptr<PreparedStatement> pstmt;
	

	try
	{
		driver = get_driver_instance();

		con.reset(driver->connect(dns, username, password));
		con->setSchema(schema);

		stmt.reset(con->createStatement());
	}
	catch(SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
	}

	try
	{
		/* Select in ascending order */
		pstmt.reset(con->prepareStatement("SELECT id FROM parking ORDER BY id ASC LIMIT 1"));
		res.reset(pstmt->executeQuery());

		/* Fetch in reverse = descending order! */
		while (res->next())
		cout << "\t... MySQL counts: " << res->getInt("id") << endl;
	} catch (SQLException &e) {
	  cout << "# ERR: SQLException in " << __FILE__;
	  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	  cout << "# ERR: " << e.what();
	  cout << " (MySQL error code: " << e.getErrorCode();
	  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	system("pause");

	return EXIT_SUCCESS;
}

