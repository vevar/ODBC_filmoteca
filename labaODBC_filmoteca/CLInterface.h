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

	//Funtions for creation new film 
	static string* inputTitle();
	static vector<Genre*>* selectGenres();
	static vector<Actor*>* selectActors();
	static double selectRating();
	static bool selectWatched();
	static void addNewGenre();
	static void addNewActor();

public:
	
	void run();

};

