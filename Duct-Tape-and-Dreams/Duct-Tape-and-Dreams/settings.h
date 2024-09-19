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

	//get maps
	std::map<string, string> getSettingMap()  {
		return settingsDict;
	}
	std::map<string, string> getSettingMapDef()  {
		return settingsDictDef;
	}

	//get setting
	std::string getSetting(string setting) {
		//cant return the string value and setting not found at the same time, as far as I know but who knows
		return settingsDict[setting];
	}

	//view maps
	int printMap(std::map<string, string> mapS);

	//settings test
	int settingTest();
};

