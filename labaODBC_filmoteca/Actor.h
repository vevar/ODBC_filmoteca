#pragma once

using namespace std;

class Actor
{
	int id;
	string firstName;
	string secondName;

public:
	Actor();
	Actor(int id, string firstName, string secondName);
	~Actor();

	void setId(int id);
	void setFirstName(string firstName);
	void setSecondName(string secondName);

	int getId();
	string getFirstName();
	string getSecondName();
};