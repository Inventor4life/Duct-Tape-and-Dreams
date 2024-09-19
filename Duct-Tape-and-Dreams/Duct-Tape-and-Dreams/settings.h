#pragma once
#include "mainheader.h"
class settings
{
private:
	std::map<string, string> settingsDict;
	std::map<string, string> settingsDictDef;

public:

	//default constructor
	settings() {};

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

	//get maps
	std::map<string, string> getSettingMap()  {
		return settingsDict;
	}
	std::map<string, string> getSettingMapDef()  {
		return settingsDictDef;
	}

	//view maps
	int printMap(std::map<string, string> mapS);

	//settings test
	int settingTest();
};

