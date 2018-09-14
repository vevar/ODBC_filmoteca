#pragma once

#include "Actor.h"

using namespace std;


class Film
{
	int id;
	string* title;
	vector<string*>*genres;
	vector<Actor*> *actors;
	double rating;
	bool watched;

public:
	Film();
	Film(int id, string* title, vector<string*>* genres,
		vector<Actor*>* actors, double rating, bool watched);
	~Film();

	void setId(int id);
	void setTitle(string* title);
	void setGenres(vector<string*>* genres);
	void setActors(vector<Actor*>* actors);
	void setRating(double rating);
	void setWatched(bool wathced);

	int getId();
	string* getTitle();
	vector<string*>* getGenres();
	vector<Actor*>* getActors();
	double getRating();
	bool getWatched();
};
