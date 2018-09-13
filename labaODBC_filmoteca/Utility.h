#pragma once

using namespace std;

class Utility
{

public:
	Utility();
	~Utility();
	/*
		Separate the str to array of strings by sep
	*/
	static vector<string> separate(string sep, string str);

};

