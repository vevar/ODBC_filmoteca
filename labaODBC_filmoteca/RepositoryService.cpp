﻿#include "pch.h"
#include "RepositoryService.h"

RepositoryService::DB::DB()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);				//Init discriptor of environment
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLAllocHandle(SQL_HANDLE_ENV)" << endl;
	}

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);	//Define version of ODBC
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLSetEnvAttr" << endl;
	}

	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);							//Init discriptor of conection 
	if (retcode != SQL_SUCCESS) {
		cout << "Error SQLAllocHandle(Conection)" << endl;
	}
}

RepositoryService::DB::~DB()
{
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
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

vector<Genre*>* RepositoryService::DB::getGenres(string str)
{
	vector<string> listIdGenres = Utility::separate(",", str.substr(1, str.size() - 2));
	vector<Genre*>* listGenres = new vector<Genre*>();

	SQLCHAR buffer[BUFFER_SIZE];
	SQLLEN sbGener;

	string query = addIdsToQuery(string("SELECT * FROM genre WHERE "), listIdGenres);
	SQLHSTMT *handler = createHandler();
	retcode = SQLExecDirectA(*handler, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(*handler);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Genre* genre = new Genre();

				SQLGetData(*handler, 1, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbGener);
				genre->setId(atoi((const char*)buffer));

				SQLGetData(*handler, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbGener);
				genre->setName(string((const char*)buffer));

				listGenres->push_back(genre);
			}
			else {
				break;
			}
		}
	}

	removeHandler(handler);

	return listGenres;
}

vector<Actor*>* RepositoryService::DB::getActors(string idsActors)
{
	vector<string> listIdActors = Utility::separate(",", idsActors.substr(1, idsActors.size() - 2));
	vector<Actor*>* listActors = new vector<Actor*>();

	SQLCHAR buffer[BUFFER_SIZE];
	SQLLEN sbIdActor, sbFirstNameActor, sbSecondNameActor;

	string query = addIdsToQuery(string("SELECT * FROM actor WHERE "), listIdActors);
	SQLHSTMT *handler = createHandler();
	retcode = SQLExecDirectA(*handler, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(*handler);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Actor* actor = new Actor();

				SQLGetData(*handler, 1, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbIdActor);
				actor->setId(atoi((const char*)buffer));

				SQLGetData(*handler, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbFirstNameActor);
				actor->setFirstName(string((const char*)buffer));

				SQLGetData(*handler, 3, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbSecondNameActor);
				actor->setSecondName(string((const char*)buffer));

				listActors->push_back(actor);
			}
			else {
				break;
			}
		}
	}

	removeHandler(handler);

	return listActors;

}

set<Genre*>* RepositoryService::DB::getAllGenres()
{

	if (!connection()) {
		return nullptr;
	}

	SQLCHAR buffer[BUFFER_SIZE];
	SQLLEN sbIdGenre, sbNameGenre;

	SQLHSTMT *handler = createHandler();

	string query = "SELECT * FROM genre";
	set<Genre*>* genres = new set<Genre*>;

	retcode = SQLExecDirectA(*handler, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(*handler);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Genre* genre = new Genre();

				SQLGetData(*handler, 1, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbIdGenre);
				genre->setId(atoi((const char*)buffer));

				SQLGetData(*handler, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbNameGenre);
				genre->setName(string((const char*)buffer));

				genres->insert(genre);
			}
			else {
				break;
			}
		}
	}

	removeHandler(handler);

	disconnect();

	return genres;
}

set<Actor*>* RepositoryService::DB::getAllActors()
{
	if (!connection()) {
		return nullptr;
	}

	SQLCHAR buffer[BUFFER_SIZE];
	SQLLEN sbIdActor, sbFirstNameActor, sbSecondName;

	SQLHSTMT *handler = createHandler();

	string query = "SELECT * FROM actor";
	set<Actor*>* actors = new set<Actor*>;

	retcode = SQLExecDirectA(*handler, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		while (TRUE) {
			retcode = SQLFetch(*handler);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Actor* actor = new Actor();

				SQLGetData(*handler, 1, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbIdActor);
				actor->setId(atoi((const char*)buffer));

				SQLGetData(*handler, 2, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbFirstNameActor);
				actor->setFirstName(string((const char*)buffer));

				SQLGetData(*handler, 3, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbSecondName);
				actor->setSecondName(string((const char*)buffer));

				actors->insert(actor);
			}
			else {
				break;
			}
		}
	}

	removeHandler(handler);

	disconnect();

	return actors;
}

set<Film*>* RepositoryService::DB::getFilmsByTitel(string title)
{
	return nullptr;
}

set<Film*>* RepositoryService::DB::getFilmsByGenre(string genre)
{
	return nullptr;
}

set<Film*>* RepositoryService::DB::getFilmsByActor(Actor actor)
{
	return nullptr;
}

set<Film*>* RepositoryService::DB::getFilmsByRatingAndWathced(int rating, bool watched)
{
	return nullptr;
}

string RepositoryService::DB::addIdsToQuery(string query, vector<string> listIds)
{
	char tmpId[] = " id=";
	char tmpOrId[] = " OR id=";

	//add tmpId
	if (listIds.size() > 0) {
		query.append(tmpId);
		query.append(listIds.at(0).c_str());
	}

	// add tmpOrId
	for (int i = 1; i < listIds.size(); i++) {
		query.append(tmpOrId);
		query.append(listIds.at(i).c_str());
	}

	return query;
}

set<Film*>* RepositoryService::DB::getAllFilm()
{
	if (!connection()) {
		return nullptr;
	}

	set<Film*> *listFilms = new set<Film*>();

	SQLCHAR selecttxt[] = "SELECT id, title, genres, actors, rating, watched  FROM film";

	SQLHSTMT* hstmt = createHandler();
	retcode = SQLExecDirectA(*hstmt, selecttxt, SQL_NTS);
	SQLLEN  sbId, sbTitle, sbGenres, sbActors, sbRating, sbWatched;

	if (retcode != SQL_SUCCESS) {
		removeHandler(hstmt);
		disconnect();

		return nullptr;
	}

	while (TRUE) {
		retcode = SQLFetch(*hstmt);
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

			//actors
			SQLGetData(*hstmt, 4, SQL_C_CHAR, &buffer, BUFFER_SIZE, &sbActors);
			film->setActors(getActors((const char *)buffer));

			//rating
			SQLGetData(*hstmt, 5, SQL_C_CHAR, &buffer, 5, &sbRating);
			film->setRating(atof((const char*)buffer));

			//watched
			SQLGetData(*hstmt, 6, SQL_C_CHAR, &buffer, 2, &sbWatched);
			bool isWatched;
			if (buffer[0] == '1') {
				isWatched = true;
			}
			else {
				isWatched = false;
			}
			film->setWatched(isWatched);

			listFilms->insert(film);
		}
		else {
			break;
		}
	}

	removeHandler(hstmt);
	disconnect();

	return listFilms;
}

bool RepositoryService::DB::addFilm(Film* film)
{
	if (!connection()) {
		return false;
	}

	SQLHSTMT *handler = createHandler();

	string query = "INSERT INTO film(title, genres, actors, rating, watched) VALUES(";
	query.append("'");
	query.append(*film->getTitle());
	query.append("'");
	query.append(",");

	query.append("'");
	query.append(film->getGenresIds());
	query.append("'");
	query.append(",");

	query.append("'");
	query.append(film->getActorsIds());
	query.append("'");
	query.append(",");
	char tmpNum[BUFFER_SIZE];
	_itoa_s(film->getRating(), tmpNum, BUFFER_SIZE, 10);
	query.append(tmpNum);
	query.append(",");
	if (film->getWatched() == true) {
		query.append("true");
	}
	else {
		query.append("false");
	}
	query.append(")");

	retcode = SQLExecDirectA(*handler, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		removeHandler(handler);
		disconnect();
		return true;
	}

	removeHandler(handler);
	disconnect();

	return false;
}

void RepositoryService::DB::editFilmById(int id)
{

}

bool RepositoryService::DB::removeFilmById(int id)
{
	if (!connection()) {
		return false;
	}

	SQLHSTMT *handler = createHandler();

	string query = "DELETE FROM film WHERE id=";
	char tmpNum[BUFFER_SIZE];
	_itoa_s(id, tmpNum, BUFFER_SIZE, 10);
	query.append(tmpNum);

	retcode = SQLExecDirectA(*handler, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		removeHandler(handler);
		disconnect();
		return true;
	}

	removeHandler(handler);
	disconnect();

	return false;
}

bool RepositoryService::DB::removeFilmByTitle(string title)
{
	return false;
}

bool RepositoryService::DB::addGenre(Genre genre)
{
	if (!connection()) {
		return false;
	}

	SQLHSTMT *handler = createHandler();

	string query = "INSERT INTO genre(genre) VALUES(";
	query.append("'");
	query.append(genre.getName());
	query.append("'");
	query.append(")");

	retcode = SQLExecDirectA(*handler, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		removeHandler(handler);
		disconnect();
		return true;
	}

	removeHandler(handler);
	disconnect();

	return false;
}

bool RepositoryService::DB::addActor(Actor actor)
{
	if (!connection()) {
		return false;
	}

	SQLHSTMT *handler = createHandler();

	string query = "INSERT INTO actor(first_name, second_name) VALUES(";
	query.append("'");
	query.append(actor.getFirstName());
	query.append("'");
	query.append(",");
	query.append("'");
	query.append(actor.getSecondName());
	query.append("'");
	query.append(")");

	retcode = SQLExecDirectA(*handler, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS) {
		removeHandler(handler);
		disconnect();
		return true;
	}

	removeHandler(handler);
	disconnect();

	return false;
}

