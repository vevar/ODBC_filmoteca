#pragma once

using namespace std;

class Genre
{
	int id;
	string name;

public:
	Genre();
	Genre(string name);
	Genre(int id, string name);
	~Genre();

	void setId(int id);
	void setName(string name);

	int getId();
	string getName();


};

