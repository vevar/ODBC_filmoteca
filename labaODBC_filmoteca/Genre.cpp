#include "pch.h"
#include "Genre.h"


Genre::Genre()
{
}

Genre::Genre(int id, string name)
{
	this->id = id;
	this->name = name;
}


Genre::~Genre()
{
}

void Genre::setId(int id)
{
	this->id = id;
}

void Genre::setName(string name)
{
	this->name = name;
}

int Genre::getId()
{
	return id;
}

string Genre::getName()
{
	return name;
}