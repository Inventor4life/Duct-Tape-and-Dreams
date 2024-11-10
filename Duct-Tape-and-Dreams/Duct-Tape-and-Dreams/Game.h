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

public:

	Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName) {
		if (!backgroundT.loadFromFile(backgroundFileLoc)) {
			std::cerr << "Failed to load background texture\n";
		}
		background.setTexture(backgroundT);
		player.spawnSprite(200, 700);
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

