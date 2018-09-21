#include "pch.h"
#include "Film.h"


Film::Film()
{
}

Film::Film(int  id, string * title, vector<Genre*>* genres,
	vector<Actor*>* actors, double  rating, bool  watched)
{
	this->id = id;
	this->title = title;
	this->genres = genres;
	this->actors = actors;
	this->rating = rating;
	this->watched = watched;
}

Film::Film(string * title, vector<Genre*>* genres, vector<Actor*>* actors, double rating, bool watched)
{
	Film(NULL, title, genres, actors, rating, watched);
}


Film::~Film()
{
	delete title;
	delete genres;
	delete actors;
}

void Film::setId(int  id)
{
	this->id = id;
}

void Film::setTitle(string * title)
{
	this->title = title;
}

void Film::setGenres(vector<Genre*>* genres)
{
	this->genres = genres;
}

void Film::setActors(vector<Actor*>* actors)
{
	this->actors = actors;
}

void Film::setRating(double  rating)
{
	this->rating = rating;
}

void Film::setWatched(bool  watched)
{
	this->watched = watched;
}

int  Film::getId()
{
	return id;
}

string * Film::getTitle()
{
	return title;
}

vector<Genre*>* Film::getGenres()
{
	return genres;
}

string Film::getGenresIds()
{
	string strIds;

	strIds.append("{");
	char * genreId;

	for (Genre* genre : *genres) {
		itoa(genre->getId(), genreId, 10);
		strIds.append(genreId);

	}
	strIds.append("}");

	return strIds;
}

vector<Actor*>* Film::getActors()
{
	return actors;
}

double Film::getRating()
{
	return rating;
}

bool Film::getWatched()
{
	return watched;
}

