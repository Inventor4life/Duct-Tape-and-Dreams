#pragma once
#include "mainheader.h"
#include "Physics.h"
class Entity : public Physics
{
public:
	Entity(string path, sf::Vector2f spawnLocation, float jumpS, float jumpH) {
		if (!texture.loadFromFile(path)) {
			cout << "No image found at: " << path << std::endl;
		}
		entitySprite.setTexture(texture);
		entitySprite.setPosition(spawnLocation.x, spawnLocation.y);
		jumpSpeed = jumpS;
		jumpHeight = jumpH;
		inAir = false;
		wasColliding = 0;
		frame = 0;
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(entitySprite);
	}

public:

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool inAir = false;
	float jumpHeight;
	float jumpSpeed;
	int wasColliding;
	int frame;
	sf::Texture texture;
	sf::Sprite entitySprite;
	sf::FloatRect objectB;
	sf::Vector2f movement;
};

