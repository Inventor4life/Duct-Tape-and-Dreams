#include "mainheader.h"
#include "Entity.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);
	//lua.script("print('bark bark bark!')");

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hatsune Miku Dance Simulator");
	sf::Event event;
	
	//making backround
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("backround.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

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
		//ah so this makes sense now! if you want to add something to your window, you gotta "draw" it on, then you can use it!
		window.draw(backgroundSprite);
		player.update(window);
		player.drawTo(window);
		window.display();
	}




	return 0;// end return 0;
}