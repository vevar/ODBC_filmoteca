#include "pch.h"
#include "Actor.h"


const char* Actor::TABLE_FIELD_ID = "id";
const char* Actor::TABLE_FIELD_FIRSTNAME = "first_name";
const char* Actor::TABLE_FIELD_SECONDNAME = "second_name";

Actor::Actor()
{
}

Actor::Actor(string firstName, string secondName)
{
	this->firstName = firstName;
	this->secondName = secondName;
}

Actor::Actor(int id, string  firstName, string secondName)
{
	this->id = id;
	this->firstName = firstName;
	this->secondName = secondName;
}


Actor::~Actor()
{
	
}

void Actor::setId(int id)
{
	this->id = id;
}

void Actor::setFirstName(string  firstName)
{
	this->firstName = firstName;
}

void Actor::setSecondName(string  secondName)
{
	this->secondName = secondName;
}

string  Actor::getFirstName()
{
	return firstName;
}

string  Actor::getSecondName()
{
	return secondName;
}

int Actor::getId()
{
	return id;
}


