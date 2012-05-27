// mssql-conn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

void show_error(unsigned int handletype, const SQLHANDLE& handle)
{
    SQLWCHAR sqlstate[1024];
    SQLWCHAR message[1024];
    if(SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
        cout<<"Message: "<<message<<"\nSQLSTATE: "<<sqlstate<<endl;
}

static SQLHANDLE env = nullptr;    
static SQLHANDLE connection = nullptr;
static SQLHANDLE statement = nullptr;
static SQLRETURN retcode;
bool init_sql(const char *dns, const char *username, const char *password);
void release_sql();

int main()
{
	int last_parming_id = -1;
	stringstream query;

    if(SQL_SUCCESS!=SQLExecDirect(sqlstatementhandle, (SQLWCHAR*)"select * from parking limit 1", SQL_NTS)){
        show_error(SQL_HANDLE_STMT, sqlstatementhandle);
        goto FINISHED;
    }
    else{
        char name[64];
        char address[64];
        int id;
        while(SQLFetch(sqlstatementhandle)==SQL_SUCCESS){
            SQLGetData(sqlstatementhandle, 1, SQL_C_ULONG, &id, 0, NULL);
            SQLGetData(sqlstatementhandle, 2, SQL_C_CHAR, name, 64, NULL);
            SQLGetData(sqlstatementhandle, 3, SQL_C_CHAR, address, 64, NULL);
            cout<<id<<" "<<name<<" "<<address<<endl;
        }
    }

FINISHED:
    SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle );
    SQLDisconnect(sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
    
}

bool init_sql(const char *dns, const char *username, const char *password)
{
	if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env))
	{
		return false;
	}

    if(SQL_SUCCESS != SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0)) 
	{
		return false;
	}

    if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, env, &connection))
	{
		return false;
	}

    SQLWCHAR retconstring[1024];
    switch(SQLDriverConnect(connection, 
                NULL, 
                (SQLWCHAR*)"DRIVER={SQL Server};SERVER=localhost, 3306;DATABASE=parking;UID=sa;PWD=admin;", 
                SQL_NTS, 
                retconstring, 
                1024, 
                NULL,
                SQL_DRIVER_NOPROMPT)){
        case SQL_SUCCESS_WITH_INFO:
            show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            break;
        case SQL_INVALID_HANDLE:
        case SQL_ERROR:
            show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            goto FINISHED;
        default:
            break;
    }
    
    if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle))
        goto FINISHED;


	return true;
}

void release_sql()
{
	if (statement != nullptr)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, statement);
	}
	
	if (connection != nullptr)
	{
		SQLDisconnect(connection);
		SQLFreeHandle(SQL_HANDLE_DBC, connection);
	}

	if (env != nullptr)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, env);
	}
}