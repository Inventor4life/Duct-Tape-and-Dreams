#include "settings.h"

int settings::loadSettings(string fileName, std::map<string, int> settingsDict) {
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
			return -20; //does this count as file not found? i guess? idk ethan elaborate to me later
		}

		//to be clear, this works off of the assumption settings are ordered as such: setting=1 or setting=0 to show true false. more detail to be added later ;3
		//nevermind can work no matter what the setting int is, but still not with strings. Shall add after lunch/gym today 

		//parsing line string into its setting value halves at the delim '=', aka pos
		string settingP = line.substr(0, pos);
		string valueP = line.substr(pos + 1);

		//storing as key-value pair in settingsDict (essentially a python dictionary but not nearly as awesome)
		settingsDict[settingP] = stoi(valueP);
		//should also overwrite duplicate settings with the one lowest down in the list. Let me know if it should be otherwise. First instance of settings remains, or last?
	}
	return 0;
}

int settings::storeSettings(string fileName, std::map<string, int> settingsDict) {
	ofstream output;
	output.open(fileName, std::ios::out);
	if (!output) cout << fileName << " failed to open.\n"; return -21;
	//pointer to first pair in map, iterate with that similairly to linked list
	std::map<string,int>::iterator ptr = settingsDict.begin();
	while (ptr != settingsDict.end()) {
		output << ptr->first << "=" << ptr->second << "\n";
		++ptr;
	}
}
