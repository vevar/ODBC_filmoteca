#include "pch.h"
#include "RepositoryService.h"

RepositoryService::DB::DB()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);	//Init discriptor of environment
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLAllocHandle(SQL_HANDLE_ENV)" << endl;
	}

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);			//Define version of ODBC
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

bool RepositoryService::DB::connection()
{
	retcode = SQLConnectA(hdbc, (SQLCHAR*) "PostgreSQL35W", SQL_NTS,
		(SQLCHAR*)NULL, 0,
		(SQLCHAR*)NULL, 0);
	
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLConnect" << endl;
		return false;
	}

	return true;
}

void RepositoryService::DB::disconnect()
{
	SQLDisconnect(hdbc);
}

SQLHSTMT RepositoryService::DB::createHandler()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode != SQL_SUCCESS)
	{
		cout << "Error SQLAllocHandle(SQL_HANDLE_STMT)" << endl;
	}

	return hstmt;
}

void RepositoryService::DB::removeHandler(SQLHSTMT* handler)
{
	SQLFreeHandle(SQL_HANDLE_STMT, handler);
}

vector<Film*>* RepositoryService::DB::getAllFilm()
{
	if (!connection()) {
		return nullptr;
	}

	vector<Film*> *listFilms = new vector<Film*>();

	SQLCHAR selecttxt[] = "SELECT id, title, genres, actors, rating, watched  FROM film";

	SQLHSTMT hstmt = createHandler();
	SQLLEN  sbId, sbTitle, sbGenres, sbActors, sbRating, sbWatched;
	retcode = SQLExecDirectA(hstmt, selecttxt, SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {

			}
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Film *film = new Film();
				SQLCHAR buffer[BUFFER_SIZE];

				//id
				SQLGetData(hstmt, 1, SQL_C_ULONG, &buffer, BUFFER_SIZE, &sbId);
				film->setId(new int(atoi((const char*)buffer)));

				//title
				SQLGetData(hstmt, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbTitle);
				film->setTitle(new string((const char*)buffer));

				//genres
				SQLGetData(hstmt, 3, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbGenres);
				//

				//actors
				SQLGetData(hstmt, 4, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbActors);
				//

				//rating
				SQLGetData(hstmt, 5, SQL_C_CHAR, &buffer, 5, &sbRating);
				film->setRating(new double(atof((const char*)buffer)));

				//watched
				SQLGetData(hstmt, 6, SQL_C_CHAR, &buffer, 2, &sbWatched);
				bool isWatched;
				if (buffer[0] == 't') {
					isWatched = true;
				} else {
					isWatched = false;
				}
				film->setWatched(new bool(isWatched));

				listFilms->push_back(film);
			}
			else {
				break;
			}
		}
		return listFilms;
	}
	
	//removeHandler(hstmt);

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
