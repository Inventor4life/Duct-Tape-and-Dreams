#include "mainheader.h"
#include "Entity.h";
#include "Physics.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::jit);

	//lua.script("print(_VERSION)");
	lua.script("print(\"Yeet!\") print(jit.version)");

	//lua.script("source.lua");

	//game window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Duct Tape and Dreams");
	sf::Event event;
	sf::Vector2f spawnLocation;
	Physics P;
	spawnLocation.x = 200.0f;
	spawnLocation.y = P.getGround();
	string path = "player.png";
	Entity player(path, spawnLocation, -15, 400);
	
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();
		window.clear();
		player.drawTo(window);
		window.display();

	}








	return 0;// end return 0;
}