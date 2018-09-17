#include "pch.h"
#include "Actor.h"


Actor::Actor()
{
}

Actor::Actor(int id, string * firstName, string* secondName)
{
	this->id = id;
	this->firstName = firstName;
	this->secondName = secondName;
}


Actor::~Actor()
{
	delete firstName;
	delete secondName;
}

void Actor::setId(int id)
{
	this->id = id;
}

void Actor::setFirstName(string * firstName)
{
	this->firstName = firstName;
}

void Actor::setSecondName(string * secondName)
{
	this->secondName = secondName;
}

string * Actor::getFirstName()
{
	return firstName;
}

string * Actor::getSecondName()
{
	return secondName;
}

int Actor::getId()
{
	return id;
}


