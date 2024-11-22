#pragma once
#include "mainheader.h"
#include "Physics.h"
class Event
{
private:
	string EventName;

	//using eventFunc = int (*)();
	std::function<int()> eventFunc;
	std::vector <std::function<int()>> eventFuncs;

public:
	Event(string str) : EventName(str) {}

	void addEventFunc(std::function<int()> funcPtr) {
		eventFuncs.push_back(funcPtr);
	}

	void trigger() {
		for (std::function<int()> funcPtr: eventFuncs) {
			int event = funcPtr();
		}
	}

};

