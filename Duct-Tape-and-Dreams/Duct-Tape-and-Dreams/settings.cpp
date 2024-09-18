#include "settings.h"

int settings::loadSettings(string fileName, std::map<string, string> settingsDict) {
	ifstream input;
	string line;
	input.open(fileName, std::ios::in);
	if (!input) { 
		cout << fileName << " failed to open.\n";
		return -21; //file failed to open;
	}

	while (!input.eof()) {
		std::size_t pos = line.find('=');
		std::getline(input, line);
		if (line == "") {
			cout << fileName << " is empty, perhaps create some settings instead!\n";
			input.close();
			return -20; //does this count as file not found? i guess? idk ethan elaborate to me later
		}

		//to be clear, this works off of the assumption settings are ordered as such: setting=1 or setting=0 to show true false. more detail to be added later ;3
		//nevermind can work no matter what the setting int is, but still not with strings. Shall add after lunch/gym today 

		//parsing line string into its setting value halves at the delim '=', aka pos
		string settingP = line.substr(0, pos);
		string valueP = line.substr(pos + 1);

		//storing as key-value pair in settingsDict (essentially a python dictionary but not nearly as awesome)
		settingsDict[settingP] = valueP;
		//should also overwrite duplicate settings with the one lowest down in the list. Let me know if it should be otherwise. First instance of settings remains, or last?
	}
	input.close();
	return 0;
}

int settings::storeSettings(string fileName, std::map<string, string> settingsDict) {
	ofstream output;
	output.open(fileName, std::ios::out);
	if (!output) cout << fileName << " failed to open.\n"; return -21;
	//pointer to first pair in map, iterate with that similairly to linked list
	std::map<string, string>::iterator ptr = settingsDict.begin();
	while (ptr != settingsDict.end()) {
		output << ptr->first << "=" << ptr->second << "\n";
		++ptr;
	}
	output.close();
}

int settings::createSettings(string settingName, string defaultValue) {\
	//validateSetting(settingName, defaultValue);

	auto key = settingsDict.find(settingName);
	if(key != settingsDict.end()){
		//setting already exists within settingsDict
		return -12;
	}
	else {
		settingsDictDef.insert({ settingName, defaultValue });
		//once settings are added to the default setting map, we can then add them  to settingsDict, whitch will be the one that is editable and such. tata!
		settingsDict.insert({ settingName, defaultValue });
		return 1;
	}
	//storing settings when added to ensure it keeps em good n safe
	storeSettings("settingsUser.txt", settingsDict);
	storeSettings("settingsDefault.txt", settingsDictDef);
}

int settings::restoreDefaultSettingsALL() {
	//clear editable settingsDict
	settingsDict.clear();
	//copy all default setting key-value pairs over to the now empty settings dict.
	settingsDict.insert(settingsDictDef.begin(), settingsDictDef.end());
	//that should be all! W bands
	return 1;
}

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
		return -11;
	}
}

int settings::editSetting(string setting, string newValue) {
	//validateSetting(setting, newValue);
	auto key = settingsDict.find(setting);
	if (key != settingsDict.end()) {
		cout << "setting: " << setting << " does not exist.\n";
		return -11;
	}
	else {
		settingsDict[setting] = newValue;
		return 0;
	}
}

int settings::deleteSetting(string setting) {
	
	auto key = settingsDict.find(setting);
	if (key != settingsDict.end()) {
		cout << "setting: " << setting << " does not exist.\n";
		return -11;
	}

	if (settingsDict[setting] != "" && settingsDict[setting] != "\0") {
		//setting is not empty. no deleting for you! go back and editSetting(setting, "\0", settingsDict) or editSetting(setting, "", settingsDict);
		cout << "setting: " << setting << " is not empty. Please call editSetting(setting, \"\0\", settingsDict) or editSetting(setting, \"\", settingsDict)";
		return -10;
	}

	else {
		settingsDict.erase(setting);
		settingsDictDef.erase(setting);
		return 0;
	}
}

//not really sure what you want here, perchance elaborate in comments
string settings::pGetSettingByName(string setting) {
	return "que pasa";
}

string settings::pGetSettingByID(string setting) {
	return "que pasa";
}