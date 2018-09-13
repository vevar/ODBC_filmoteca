#pragma once

using namespace std;

class Actor
{
	string *firstName;
	string *secondName;

public:
	Actor();
	Actor(string* firstName, string* secondName);
	~Actor();

	void setFirstName(string* firstName);
	void setSecondName(string* secondName);

	string* getFirstName();
	string* getSecondName();
};