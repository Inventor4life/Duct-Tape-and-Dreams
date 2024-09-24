#include "settings.h"


/*Function: loadSettings
Description: reads from settingsUser.txt to load previously made settings into the game*/
int settings::loadSettings(string fileName, std::map<string, string> settingsDict) {
	ifstream input;
	string line;
	int bad = 0;
	input.open(fileName, std::ios::in);
	if (!input) { 
		cout << fileName << " failed to open.\n";
		return FILE_ERROR; //file failed to open;
	}

	while (!input.eof()) {
		std::getline(input, line);
		std::size_t pos = line.find('=');
		if (pos != std::string::npos && pos!=0 && line[pos]!='=') {
			//line did have the delimeter in it, so the line parsing may continue, otherwise, itll just skip it.
			if (line == "") {
				cout << fileName << " is empty, perhaps create some settings instead!\n";
				input.close();
				return FILE_NOT_FOUND; //does this count as file not found? i guess? idk ethan elaborate to me later
			}

			//to be clear, this works off of the assumption settings are ordered as such: setting=1 or setting=0 to show true false. more detail to be added later ;3
			//nevermind can work no matter what the setting int is, but still not with strings. Shall add after lunch/gym today 

			//parsing line string into its setting value halves at the delim '=', aka pos
			string settingP = line.substr(0, pos);
			string valueP = line.substr(pos + 1);

			//storing as key-value pair in settingsDict (essentially a python dictionary but not nearly as awesome)
			auto key = settingsDict.find(settingP);
			if (key != settingsDict.end()) {
				settingsDict[settingP] = valueP;
			}
			else bad = 1;
			//should also overwrite duplicate settings with the one lowest down in the list. Let me know if it should be otherwise. First instance of settings remains, or last?
		}
	}
	input.close();
	if (bad) return BAD_INPUT;
	else return 0;
}

/*Function: storeSettings
Description: stores current settings map into settingsUser.txt*/
int settings::storeSettings(string fileName, std::map<string, string> settingsDict) {
	ofstream output;
	output.open(fileName, std::ios::out);
	if (!output) { cout << fileName << " failed to open.\n"; return FILE_ERROR; }
	//pointer to first pair in map, iterate with that similairly to linked list
	std::map<string, string>::iterator ptr = settingsDict.begin();
	while (ptr != settingsDict.end()) {
		output << ptr->first << "=" << ptr->second << "\n";
		++ptr;
	}
	output.close();
}

/*Function: createSettings
Description: creates new setting-default value pair in settings map*/
int settings::createSettings(string settingName, string defaultValue) {\
	//validateSetting(settingName, defaultValue);

	auto key = settingsDict.find(settingName);
	if(key != settingsDict.end()){
		//setting already exists within settingsDict
		return SETTING_ALREADY_EXISTS;
	}
	else {
		settingsDictDef.insert({ settingName, defaultValue });
		//once settings are added to the default setting map, we can then add them  to settingsDict, whitch will be the one that is editable and such. tata!
		settingsDict.insert({ settingName, defaultValue });
		return 0;
	}
	//storing settings when added to ensure it keeps em good n safe
	storeSettings("settingsUser.txt", settingsDict);
	storeSettings("settingsDefault.txt", settingsDictDef);
}

/*Function: restoreDefaultSettingsALL
Description: restores ALL settings to their default values*/
int settings::restoreDefaultSettingsALL() {
	//clear editable settingsDict
	settingsDict.clear();
	//copy all default setting key-value pairs over to the now empty settings dict.
	settingsDict.insert(settingsDictDef.begin(), settingsDictDef.end());
	//that should be all! W bands
	return 0;
}

/*Function: restoreDefaultSetting
Description: resets specified setting to its default value*/
int settings::restoreDefaultSetting(string setting) {
	auto key = settingsDict.find(setting);
	auto keyDef = settingsDict.find(setting);

	if (key != settingsDict.end() && keyDef != settingsDictDef.end()) {
		//it exists! in both maps! time to restore it!
		settingsDict[setting] = settingsDictDef[setting];
		return 0;
	}
	else {
		cout << "setting: " << setting << " does not exist.\n";
		return SETTING_NOT_FOUND;
	}
}

/*Function: editSetting
Description: edits setting value in setting map*/
int settings::editSetting(string setting, string newValue) {
	//validateSetting(setting, newValue);
	auto key = settingsDict.find(setting);
	if (key == settingsDict.end()) {
		cout << "setting: " << setting << " does not exist.\n";
		return SETTING_NOT_FOUND;
	}
	else {
		settingsDict[setting] = newValue;
		return 0;
	}
}

/*Function: deleteSetting
Description: deletes a setting from setting map after confirming its value is null*/
int settings::deleteSetting(string setting) {
	
	auto key = settingsDict.find(setting);
	if (key != settingsDict.end()) {
		cout << "setting: " << setting << " does not exist.\n";
		return SETTING_NOT_FOUND;
	}

	if (settingsDict[setting] != "" && settingsDict[setting] != "\0") {
		//setting is not empty. no deleting for you! go back and editSetting(setting, "\0", settingsDict) or editSetting(setting, "", settingsDict);
		cout << "setting: " << setting << " is not empty. Please call editSetting(setting, \"\0\", settingsDict) or editSetting(setting, \"\", settingsDict)";
		return INVALID_VALUE;
	}

	else {
		settingsDict.erase(setting);
		settingsDictDef.erase(setting);
		return 0;
	}
}

/*Function: printMap
Description: prints currently loaded settings in setting map*/
int settings::printMap(std::map<string, string> mapS) {
	std::map<string, string>::iterator ptr = mapS.begin();
	while (ptr != mapS.end()) {
		cout << ptr->first << "=" << ptr->second << "\n";
		++ptr;
	}
	return 0;
}

/*Function: settingTest
Description: test case function designed to run numerous tests on setting class member functions*/
int settings::settingTest() {
	//testing settings:
	settings s;
	std::map<string, string> mapS;
	std::map<string, string> mapSD;

	s.createSettings("userName", "none");
	s.createSettings("fullscreen", "FALSE");
	s.createSettings("diffuculty", "1");
	s.createSettings("autoRun", "TRUE");

	mapS = s.getSettingMap();
	mapSD = s.getSettingMapDef();

	s.printMap(mapS);
	//s.printMap(mapSD);

	s.editSetting("userName", "JoeShmoe");

	mapS = s.getSettingMap();
	mapSD = s.getSettingMapDef();

	s.storeSettings("settingsUser.txt", mapS);

	cout << "\n";
	s.printMap(mapS);
	//s.printMap(mapSD);

	s.restoreDefaultSettingsALL();

	mapS = s.getSettingMap();
	mapSD = s.getSettingMapDef();
	
	cout << "\n";
	s.printMap(mapS);
	//s.printMap(mapSD);



	return 1;
}

/*Function: verifySettings
Description: checks to ensure function inputs are valid*/
int settings::verifySetting(string setting, string value) {

	//checks the inputted setting to see if it exists, then checks the inputted value to check if it is a valid setting option
	//time to hard code in literally every setting we have WEEEEEEEE (;-;)
	
	//not sure if theres some fancy coding man way of doing this better, but for now it exists as such. More to be fine tuned latah

	if (setting == "SprintMode") {
		if (value == "Toggle" || value == "Hold") return 1;
		else return 0;
	}
	if (setting == "SprintMode") {
		if (value == "Toggle" || value == "Hold") return 1;
		else return 0;
	}
	if (setting == "MoveUp" || "MoveDown" || "MoveLeft" || "MoveRight" || "Interact" || "Drop" || "Attach" || "Detach") {
		if (isalpha(value[0]) && value.size() == 1) return 1;
		else return 0;
	}
	if (setting == "ClimbMode") {
		if (value == "Interact" || value == "HoldUp") return 1;
		else return 0;
	}
	if (setting == "CameraShake" || setting == "Multiplayer") {
		if (value == "TRUE" || value == "FALSE") return 1;
		else return 0;
	}
	if (setting == "Diffuculty") {
		if (value == "1" || value == "2" || value == "3" || value == "4") return 1;
		else return 0;
	}
	if (setting == "MasterVolume" || setting == "SFXVolume" || setting == "MusicVolume" || setting == "DialogueVolume") {
		if (stoi(value) >= 0 && stoi(value) <= 100) return 1;
		else return 0;
	}
	if (setting == "Resolution") {
		if (value == "1920x1080" || value == "2440x1440") return 1;//gonna need to make more of these later
		else return 0;
	}
	if (setting == "FrameRate") {
		if (value == "30" || value == "60" || value == "unlimited") return 1;
		else return 0;
	}
	return 0;

}

