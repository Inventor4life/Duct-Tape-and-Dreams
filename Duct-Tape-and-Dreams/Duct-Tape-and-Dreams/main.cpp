#include "mainheader.h"
#include "Entity.h"
#include "Object.h"
int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);
	//lua.script("print('bark bark bark!')");

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hatsune Miku Dance Simulator");
	sf::Event event;
	
	//making backround
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Backrounds/backround.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	Entity player;
	Object HatsuObject("Objects/HatsuObject.png", 800.0f, 500.f);
	Object p1("Objects/platform1.png", 1300.0f, 700.f);
	sf::Clock clock;

	//opens the actual window and keeps it on
	while (window.isOpen()) {
		sf::Time deltaTime = clock.restart();

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
		window.draw(backgroundSprite);
		HatsuObject.drawTo(window);
		p1.drawTo(window);
		player.update(window, deltaTime.asSeconds(), HatsuObject, p1);
		player.drawTo(window);
		window.display();
	}




	return 0;// end return 0;
}