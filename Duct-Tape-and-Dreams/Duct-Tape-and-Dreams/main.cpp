#include "mainheader.h"
#include "Entity.h";
#include "Physics.h"
#include "Event.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::jit);

	//lua.script("print(_VERSION)");
	lua.script("print(\"Yeet!\") print(jit.version)");

	Game G;
	G.runGame();

	return 0;// end return 0;
}