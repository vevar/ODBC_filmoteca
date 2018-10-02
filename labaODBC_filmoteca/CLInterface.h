#pragma once

#include "RepositoryService.h"


using namespace std;

class CLInterface
{
	RepositoryService reposService;

	static void printFilm(Film film);
	static void printMenu();

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

	void addNewGenre();
	void addNewActor();

	int  inputIdFilm();

public:
	
	void run();

};

