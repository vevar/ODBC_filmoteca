#pragma once

using namespace std;



class Genre
{
	int id;
	string name;

public:

	static const char* TABLE_FIELD_ID;
	static const char* TABLE_FIELD_NAME;

	Genre();
	Genre(string name);
	Genre(int id, string name);
	~Genre();

	void setId(int id);
	void setName(string name);

	int getId();
	string getName();


};

