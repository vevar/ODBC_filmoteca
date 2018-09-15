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

SQLHSTMT* RepositoryService::DB::createHandler()
{
	SQLHSTMT* handler = new SQLHSTMT();
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &*handler);

	if (retcode != SQL_SUCCESS)
	{
		cout << "Error SQLAllocHandle(SQL_HANDLE_STMT)" << endl;
	}

	return handler;
}

void RepositoryService::DB::removeHandler(SQLHSTMT* handler)
{
	SQLFreeHandle(SQL_HANDLE_STMT, handler);
	delete handler;
}

vector<string*>* RepositoryService::DB::getGenres(string str)
{
	vector<string> listIdGenres = Utility::separate(",", str.substr(1, str.size()-2));
	vector<string*>* listGenres = new vector<string*>();

	SQLCHAR buffer[BUFFER_SIZE];
	SQLLEN sbGener;

	SQLCHAR tmpQueryGenres[] = "SELECT genre FROM genre WHERE id=";
	char tmpStrId[] = " OR id= ";

	char* query = new char(strlen((const char*)tmpQueryGenres));
	strcpy_s(query, BUFFER_SIZE, (const char*)tmpQueryGenres);

	for (int i = 0; i < listIdGenres.size(); i++)
	{
		if (i > 0){
			char* strchId = new char(strlen(tmpStrId));
			strcpy_s(strchId, BUFFER_SIZE, tmpStrId);
			
			strcat_s(strchId, 255, listIdGenres[i].c_str());
			strcat_s(query, 255, strchId);
		} else {
			strcat_s(query, 255, listIdGenres[i].c_str());
		}
	}

	SQLHSTMT *hstmt = createHandler();

	retcode = SQLExecDirectA(*hstmt, (SQLCHAR*)(const char*)query, SQL_NTS);

	while (TRUE) {
		retcode = SQLFetch(*hstmt);
		if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {

		}
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			SQLGetData(*hstmt, 1, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbGener);
			listGenres->push_back(new string((const char*)buffer));
		}
		else {
			break;
		}
	}

	removeHandler(hstmt);

	return listGenres;
}

vector<Film*>* RepositoryService::DB::getAllFilm()
{
	if (!connection()) {
		return NULL;
	}

	vector<Film*> *listFilms = new vector<Film*>();

	SQLCHAR selecttxt[] = "SELECT id, title, genres, actors, rating, watched  FROM film";

	SQLHSTMT* hstmt = createHandler();
	SQLLEN  sbId, sbTitle, sbGenres, sbActors, sbRating, sbWatched;
	retcode = SQLExecDirectA(*hstmt, selecttxt, SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(*hstmt);
			if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {

			}
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Film *film = new Film();
				SQLCHAR buffer[BUFFER_SIZE];

				//id
				SQLGetData(*hstmt, 1, SQL_CHAR, &buffer, BUFFER_SIZE, &sbId);
				film->setId(atoi((const char *)buffer));

				//title
				SQLGetData(*hstmt, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbTitle);
				film->setTitle(new string((const char*)buffer));

				//genres
				SQLGetData(*hstmt, 3, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbGenres);
				film->setGenres(getGenres((const char*)buffer));
				//

				//actors
				SQLGetData(*hstmt, 4, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbActors);
				//

				//rating
				SQLGetData(*hstmt, 5, SQL_C_CHAR, &buffer, 5, &sbRating);
				film->setRating(atof((const char*)buffer));

				//watched
				SQLGetData(*hstmt, 6, SQL_C_CHAR, &buffer, 2, &sbWatched);
				bool isWatched;
				if (buffer[0] == '1') {
					isWatched = true;
				} else {
					isWatched = false;
				}
				film->setWatched(isWatched);

				listFilms->push_back(film);
			}
			else {
				break;
			}
		}
		return listFilms;
	}
	
	removeHandler(hstmt);

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
