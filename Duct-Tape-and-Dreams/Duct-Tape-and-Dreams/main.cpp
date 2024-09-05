#include "mainheader.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('bark bark bark!')");

	return 0;
}