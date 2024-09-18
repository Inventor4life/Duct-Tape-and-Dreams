#pragma once
#include "mainheader.h"
class settings
{
private:
	string fileName;
	std::map<string, string> settingsDict;
	std::map<string, string> settingsDictDef;

public:

	//default constructor
	settings() : fileName("settingsUser.txt") {};

	//opens settings txt, reads current settings
	int loadSettings(string fileName, std::map<string, string> settingsDict);

	//store settings into txt. something to keep in mind.
	int storeSettings(string fileName, std::map<string, string> settingsDict);

	//create settings, calling both loadSettings and storeSettings
	int createSettings(string settingName, string defaultValue);

	//restoring default settings, essentially settingsDict = settingsDictDef
	int restoreDefaultSettingsALL();
	int restoreDefaultSetting(string setting);

	//edit settings
	int editSetting(string setting, string newValue);

	//delete settings
	int deleteSetting(string setting);

	//get settings
	string pGetSettingByName(string setting);
	string pGetSettingByID(string setting);

};

