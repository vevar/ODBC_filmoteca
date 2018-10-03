#pragma once

#include "RepositoryService.h"

#define MESSAGE_FILM_NOT_FOUND "Film not found."
#define MESSAGE_INCORRECT_INPUT "Incorrect input."

#define MESSAGE_ERROR_UPDATE "Error update."
#define MESSAGE_ERROR_INSERT "Error insert."
#define MESSAGE_ERROR_DELETE "Errro delete."

using namespace std;

class CLInterface
{
	RepositoryService reposService;

	void printFilm(Film film);
	void printFilms(set<Film*>* film);

	//Kinds of menu
	void printMenu();
	void printFilmEditMenu();
	void printSearchMenu();

	//Menu functins
	void printAllFilms();
	void addFilm();
	void editFilm();
	void removeFilm();
	void searchFilm();

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
	
	//Function of edit menu
	void editFilmTitle();
	void editFilmGenre();
	void editFilmActor();
	void editFilmRating();
	void editFilmWatched();
	
	//Functions of search menu
	void searchByTitle();
	void searchByGenre();
	void searchByActor();
	void searchByRatingNotWatched();

	//Info
	void printMessage(const char* str);

public:
	
	void run();

};

