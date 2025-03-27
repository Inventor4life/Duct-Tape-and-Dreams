#include <iostream>
#include <sol/sol.hpp>
#include <steam/steam_api.h>

int main()
{
	// Verify SteamAPI installation
	if(!SteamAPI_Init()) {
	return -1;
	}
	SteamAPI_Shutdown();

	// Verify sol2/Lua/LuaJIT installation
	sol::state lua;
	lua.open_libraries(sol::lib::jit, sol::lib::base);
	lua.script("print(jit.version)");

	return 0;
}
