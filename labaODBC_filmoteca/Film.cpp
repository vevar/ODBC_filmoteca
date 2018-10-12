#include "pch.h"
#include "Film.h"

const char* Film::TABLE_NAME = "film";
const char* Film::TABLE_FIELD_ID = "id";
const char* Film::TABLE_FIELD_TITLE = "title";
const char* Film::TABLE_FIELD_ACTOR = "actor";
const char* Film::TABLE_FIELD_GENRE = "genre";

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

Film::Film(string * title, vector<Genre*>* genres, vector<Actor*>* actors, double rating, bool watched):Film(NULL, title, genres, actors, rating, watched)
{
	
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
	if (genres->size() > 0) {
		strIds.append("{");
		char  genreId[255];

		int size = genres->size() - 1;
		for (int i = 0; i < size; i++)
		{
			_itoa_s(genres->at(i)->getId(), genreId, 255, 10);
			strIds.append(genreId);
			strIds.append(",");
		}
		_itoa_s(genres->at(size)->getId(), genreId, 255, 10);

		strIds.append(genreId);
		strIds.append("}");

	}
	
	return strIds;
}

vector<Actor*>* Film::getActors()
{
	return actors;
}

string Film::getActorsIds()
{
	string strIds;
	if (actors->size() > 0){
		strIds.append("{");
		char actorId[255];

		int size = actors->size() - 1;
		for (int i = 0; i < size; i++)
		{
			_itoa_s(actors->at(i)->getId(), actorId, 255, 10);
			strIds.append(actorId);
			strIds.append(",");
		}
		_itoa_s(actors->at(size)->getId(), actorId, 255, 10);

		strIds.append(actorId);
		strIds.append("}");

	}
	
	return strIds;
}

double Film::getRating()
{
	return rating;
}

bool Film::getWatched()
{
	return watched;
}

