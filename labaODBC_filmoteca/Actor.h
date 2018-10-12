#pragma once

using namespace std;


class Actor
{
	int id;
	string firstName;
	string secondName;

public:

	static const char* TABLE_FIELD_ID;
	static const char* TABLE_FIELD_FIRSTNAME;
	static const char* TABLE_FIELD_SECONDNAME;

	Actor();
	Actor(string firstName, string secondName);
	Actor(int id, string firstName, string secondName);
	~Actor();

	void setId(int id);
	void setFirstName(string firstName);
	void setSecondName(string secondName);

	int getId();
	string getFirstName();
	string getSecondName();
};