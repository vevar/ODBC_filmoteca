#pragma once

#include "Film.h"
#include "Utility.h"

using namespace std;

#define BUFFER_SIZE 255

class RepositoryService
{
	class DB {

		SQLHENV     henv;		// Descriptor of environment
		SQLHDBC     hdbc; 		// Descriptor of conection
		SQLRETURN   retcode; 	// Code of return

		/*
			Create connection with datebase;
		*/
		bool connection();
		/*
			Break connection with datebase;
		*/
		void disconnect();

		SQLHSTMT* createHandler();
		void removeHandler(SQLHSTMT* handler);

		vector<Genre*>* getGenres(string);
		vector<Actor*>* getActors(string idsActors);

		string addIdsToQuery(string query, vector<string> listIds);

	public:

		DB();
		~DB();

		SQLRETURN getCodeReturn();

		set<Film*>* getAllFilm();
		set<Genre*>* getAllGenres();
		set<Actor*>* getAllActors();

		set<Film*>* getFilmsByTitel(string title);
		set<Film*>* getFilmsByGenre(string genre);
		set<Film*>* getFilmsByActor(Actor actor);
		set<Film*>* getFilmsByRatingAndWathced(int rating, bool watched);

		bool addFilm(Film* film);

		void editFilmById(int id);

		bool removeFilmById(int id);
		bool removeFilmByTitle(string title);
		bool addGenre(Genre genre);
		bool addActor(Actor actor);

	};

	DB* db;

public:

	DB* getDB() {
		if (db == nullptr)
		{
			db = new DB();
		}
		return db;
	}

};

