#pragma once
#include "mainheader.h"
class settings
{
private:
	string fileName;
	ifstream input;
	//for now just testing with settings each having 1's or 0's to show true/false on settings
	std::map<string, int> settingsDict;

public:

	//default constructor
	settings() : fileName("settingsUser.txt") {};

	//opens settings txt, reads current settings
	int loadSettings(string fileName, std::map<string,int> settingsDict);

	//store settings into txt. something to keep in mind.
	int storeSettings(string fileName, std::map<string, int> settingsDict);

	//create settings, calling both loadSettings and storeSettings
};

