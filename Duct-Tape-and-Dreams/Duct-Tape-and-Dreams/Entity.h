#pragma once
#include "mainheader.h"
#include "Physics.h"
class Entity : private Physics 
{
private:
	sf::Texture texture;
	sf::Sprite entitySprite;
	sf::Vector2f pos;
	std::vector<float> forces;
	sf::Window* window; //why? o.O

	//assorted funky lua shit 

public:
	Entity() {}

	void makeSprite(string pngLocation) {
		if (!texture.loadFromFile(pngLocation)) {
			cout << "Failed to load texture: " << pngLocation << "\n";
		}
		entitySprite.setTexture(texture);
	}

	void setForces(std::vector<float> newForces) {
		int i = 0;
		for (float& force : forces) {  
			force = newForces[i++];    
		}
	}

	void spawnSprite(float x, float y) {
		pos.x = x, pos.y = y;
		entitySprite.setPosition(x, y);
	}

	sf::Vector2f updatePos(float x, float y) {
		pos.x = x, pos.y = y;
		entitySprite.setPosition(x, y);
		return pos;
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(entitySprite);
	}
};
