#pragma once

#include "RepositoryService.h"


using namespace std;

class CLInterface
{
	static void printFilm(Film film);
	static void printMenu();

	//Menu functins
	static void printAllFilms();
	static void printFilm();
	static void addFilm();
	static void editFilm();
	static void removeFilm();

public:
	
	void run();

};

