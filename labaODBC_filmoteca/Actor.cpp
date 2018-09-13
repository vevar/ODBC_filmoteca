#include "pch.h"
#include "Actor.h"


Actor::Actor()
{
}

Actor::Actor(string * firstName, string* secondName)
{
	this->firstName = firstName;
	this->secondName = secondName;
}


Actor::~Actor()
{
	delete firstName;
	delete secondName;
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


