#include "pch.h"
#include "Utility.h"


Utility::Utility()
{
}


Utility::~Utility()
{
}


vector<string> Utility::separate(string sep, string str)
{
	vector<string> arr;
	size_t prev = 0;
	size_t next;
	size_t delta = sep.length();

	while ((next = str.find(sep, prev)) != string::npos) {
		string tmp = str.substr(prev, next - prev);
		arr.push_back(str.substr(prev, next - prev));
		prev = next + delta;
	}

	string tmp = str.substr(prev);
	arr.push_back(str.substr(prev));

	return arr;
}
