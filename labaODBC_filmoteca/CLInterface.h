#pragma once

#include "RepositoryService.h"


using namespace std;

class CLInterface
{
	RepositoryService reposService;

	void printFilm(Film film);
	void printMenu();
	void printFilmEditMenu();

	//Menu functins
	void printAllFilms();
	void printFilm();
	void addFilm();
	void editFilm();
	void removeFilm();

	//Funtions for creation new film 
	string* inputTitle();
	vector<Genre*>* selectGenres();
	vector<Actor*>* selectActors();
	double selectRating();
	bool selectWatched();

	//Other functions
	void addNewGenre();
	void addNewActor();

	int  inputIdFilm();
	
	//Edit functions
	void editFilmTitle();
	void editFilmGenre();
	void editFilmActor();
	void editFilmRating();
	void editFilmWatched();

public:
	
	void run();

};

