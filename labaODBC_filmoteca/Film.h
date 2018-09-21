#pragma once

#include "Actor.h"
#include "Genre.h"

using namespace std;


class Film
{
	int id;
	string* title;
	vector<Genre*>*genres;
	vector<Actor*> *actors;
	double rating;
	bool watched;

public:
	Film();
	Film(int id, string* title, vector<Genre*>* genres,
		vector<Actor*>* actors, double rating, bool watched);
	Film(string* title, vector<Genre*>* genres,
		vector<Actor*>* actors, double rating, bool watched);
	~Film();

	void setId(int id);
	void setTitle(string* title);
	void setGenres(vector<Genre*>* genres);
	void setActors(vector<Actor*>* actors);
	void setRating(double rating);
	void setWatched(bool wathced);

	int getId();
	string* getTitle();
	vector<Genre*>* getGenres();
	string getGenresIds();
	vector<Actor*>* getActors();
	string getActorsIds();

	double getRating();
	bool getWatched();
};
