#include <steam/steam_api.h>

int main()
{
	if(!SteamAPI_Init()) {
	return -1;
	}
	SteamAPI_Shutdown();
	return 0;
}