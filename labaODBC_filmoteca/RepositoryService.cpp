#include "pch.h"
#include "RepositoryService.h"

RepositoryService::DB::DB()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);	//Init discriptor of environment
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLAllocHandle(SQL_HANDLE_ENV)" << endl;
	}

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,				//Define version of ODBC
		(void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLSetEnvAttr" << endl;
	}

	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);				//Init discriptor of conection 
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLAllocHandle(Conection)" << endl;
	}
}

RepositoryService::DB::~DB()
{

}

SQLRETURN RepositoryService::DB::getCodeReturn()
{
	return retcode;
}

vector<Film*>* RepositoryService::DB::getAllFilm()
{

	return nullptr;
}

void RepositoryService::DB::addFilm(Film film)
{
}

void RepositoryService::DB::editFilmById(int id)
{
}

void RepositoryService::DB::removeFilmById(int id)
{
}

void RepositoryService::DB::removeFilmByTitle(string title)
{
}
