#pragma once

#include "Film.h"

using namespace std;

#define BUFFER_SIZE 255

class RepositoryService
{	
	class DB {

		SQLHENV     henv;		// Descriptor of environment
		SQLHDBC     hdbc; 		// Descriptor of conection
		SQLRETURN   retcode; 	// Code of return

	public:
		
		DB();
		~DB();

		SQLRETURN getCodeReturn();

		vector<Film*>* getAllFilm();

		void addFilm(Film film);

		void editFilmById(int id);

		void removeFilmById(int id);
		void removeFilmByTitle(string title);



	};

	static DB* db;

public:

	static DB* getDB() {
		if (db == nullptr)
		{
			db = new DB();
		}
		return db;
	}
	
};

