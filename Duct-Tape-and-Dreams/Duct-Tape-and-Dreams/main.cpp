#include "mainheader.h"
#include "Entity.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);
	//lua.script("print('bark bark bark!')");

	sf::RenderWindow window(sf::VideoMode(600, 400), "Hatsune Miku Dance Simulator");
	sf::Event event;
	
	Entity player;

	//opens the actual window and keeps it on
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {  
				player.processEvents(event.key.code, true);

			}
			if (event.type == sf::Event::KeyReleased) {  
				player.processEvents(event.key.code, false);
			}
		}
		window.clear();
		player.update();
		player.drawTo(window);
		window.display();
	}




	return 0;// end return 0;
}