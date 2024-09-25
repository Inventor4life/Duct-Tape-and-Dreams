#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "mainheader.h"
#include <iostream>
class Entity
{
public:
	Entity() {
		if (!texture.loadFromFile("player.png")) {
			std::cout << "no player png found";
		}
		entitySprite.setTexture(texture);
		entitySprite.setPosition(100.f, 100.f);
	}

	bool up = false;
	bool down = false;
	bool left= false;
	bool right= false;

	void processEvents(sf::Keyboard::Key key, bool isPressed) {
		if (key == sf::Keyboard::W) {
			up = isPressed;
		}
		if (key == sf::Keyboard::S) {
			down = isPressed;
		}
		if (key == sf::Keyboard::A) {
			left = isPressed;
		}
		if (key == sf::Keyboard::D) {
			right = isPressed;
		}
	}
	void update() {
		float speed = 0.05f; // changes speed of sprite (ITS REALLY FAST FOR SOME REASON)
		sf::Vector2f movement(0.f, 0.f);

		if (up) movement.y -= speed;
		if (down) movement.y += speed;
		if (left) movement.x -= speed;
		if (right) movement.x += speed;

		entitySprite.move(movement);
	}


	void drawTo(sf::RenderWindow &window) {
		window.draw(entitySprite);
	}

private:
	sf::Texture texture;  
	sf::Sprite entitySprite;

};

