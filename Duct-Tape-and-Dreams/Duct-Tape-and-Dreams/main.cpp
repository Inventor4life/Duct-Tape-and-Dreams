#include "mainheader.h"
#include "settings.h"
int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('bark bark bark!')");

	//testing settings:
	settings s;
	s.createSettings("userName", "none");
	s.createSettings("fullscreen", "FALSE");
	s.createSettings("diffuculty", "1");
	s.createSettings("autoRun", "TRUE");

	

	return 0;// end return 0;
}