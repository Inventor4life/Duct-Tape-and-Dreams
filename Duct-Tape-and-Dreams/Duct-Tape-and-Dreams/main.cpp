#include "mainheader.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print(_VERSION)");

	//lua.script("source.lua");

	return 0;// end return 0;
}