#pragma once
#include "mainheader.h"
#include "Physics.h"
class Event
{
private:
	string EventName;

	using eventFunc = Event* (*)();
	std::vector<eventFunc> eventFuncs;

public:
	Event(string str) : EventName(str) {}

	void addEventFunc(eventFunc funcPtr) {
		eventFuncs.push_back(funcPtr);
	}

	void trigger() {
		for (eventFunc funcPtr: eventFuncs) {
			Event* event = funcPtr();
		}
	}

};

