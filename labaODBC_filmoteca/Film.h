#pragma once

#include "Actor.h"

using namespace std;


class Film
{
	int *id;
	string *title;
	vector<string*> *genres;
	vector<Actor*> *actors;
	string *rating;
	string *watched;

public:
	Film();
	Film(int* id, string* title, vector<string*>* genres,
		vector<Actor*>* actors, string* rating, string* watched);
	~Film();

	void setId(int * id);
	void setTitle(string* title);
	void setGenres(vector<string*>* genres);
	void setActors(vector<Actor*>* actors);
	void setRating(string* rating);
	void setWatched(string* wathced);

	int* getId();
	string* getTitle();
	vector<string*>* getGenres();
	vector<Actor*>* getActors();
	string* getRating();
	string* getWatched();
};
