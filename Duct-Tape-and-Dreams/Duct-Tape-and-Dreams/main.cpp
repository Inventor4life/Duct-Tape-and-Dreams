#include "mainheader.h"
#include "settings.h"
int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('bark bark bark!')");
	
	settings s;
	s.settingTest();
	return 0;// end return 0;
}