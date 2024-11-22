#pragma once
#include "mainheader.h"
#include "Entity.h"
#include "Event.h"

class Game
{

private:
	int resX;
	int resY;
	std::string windowName = "Duct tape and tears";
	sf::RenderWindow window;
	sf::Event event;
	sf::Texture backgroundT;
	sf::Sprite background;
	Entity player;
	std::string playerFileLoc = "player.png";
	std::string backgroundFileLoc = "backround.png";

	sf::Clock clock;
	sf::Time deltaTime;

	std::vector<Event> events{};

public:

	Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName) {
		if (!backgroundT.loadFromFile(backgroundFileLoc)) {
			std::cerr << "Failed to load background texture\n";
		}
		background.setTexture(backgroundT);
		player.makeSprite(playerFileLoc);
		player.spawnSprite(200, 600);
	}


	//INITIALIZER
	void initializer() {
		//initializing default controllers:
		Event jump("jump");
		jump.addEventFunc(jumpMath());
	}

	//CONTROLLER
	void controller(sf::Keyboard::Key input) {
		jump.trigger();
	}






	void runGame() {
		while (window.isOpen()) {
			deltaTime = clock.restart();
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			window.clear();
			window.draw(background);
			player.drawTo(window);
			window.display();
		}
	}




};

