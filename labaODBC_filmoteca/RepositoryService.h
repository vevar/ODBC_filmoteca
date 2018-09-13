#pragma once

#include "Film.h"

using namespace std;

#define BUFFER_SIZE 255

class RepositoryService
{
	SQLHENV     henv;		// Descriptor of environment
	SQLHDBC     hdbc; 		// Descriptor of conection
	SQLHSTMT    hstmt; 		// Descriptor of operator
	SQLRETURN   retcode; 	// Code of return
	

public:
	RepositoryService();
	~RepositoryService();

	vector<Film> getAllFilm();
	
	void addFilm(Film film);

	void editFilmById(int id);

	void removeFilmById(int id);
	void removeFilmByTitle(string title);

};

