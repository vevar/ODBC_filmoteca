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


		bool checkFilmTable();
		bool checkGenreTable();
		bool checkActorTable();

		bool checkFilmFields();
		bool checkGenreFields();
		bool checkActorFields();

		bool checkTableExist(string nameTable);

		bool createTableFilm();
		bool createTableGenre();
		bool createTableActor();


	public:

		DB();
		~DB();

		SQLRETURN getCodeReturn();

		set<Film*>* getAllFilm();
		set<Genre*>* getAllGenres();
		set<Actor*>* getAllActors();

		set<Film*>* getFilmsByTitle(string title);
		set<Film*>* getFilmsByGenres(vector<Genre*>* genres);
		set<Film*>* getFilmsByActors(vector<Actor*>* actors);
		set<Film*>* getFilmsByRatingAndWathced(int rating, bool watched);

		bool addFilm(Film* film);
		bool addGenre(Genre genre);
		bool addActor(Actor actor);

		bool updateTitleById(int id, string title);
		bool updateGenreById(int id, vector<Genre*>* genres);
		bool updateActorById(int id, vector<Actor*>* actors);
		bool updateRatingById(int id, double rating);
		bool updateWatchedById(int id, bool watched);

		bool removeFilmById(int id);
		bool removeFilmByTitle(string title);
		
		bool checkTablesDataBase();

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

