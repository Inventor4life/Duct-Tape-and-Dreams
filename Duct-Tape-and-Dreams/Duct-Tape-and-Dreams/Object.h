#pragma once
#include "mainheader.h"


class Object
{
public:

	Object(std::string png, float x, float y) {
		if (!texture.loadFromFile(png)) {
			std::cout << "no object png found";
		}
		objectSprite.setTexture(texture);
		objectSprite.setPosition(x, y);
		sf::Vector2u textureSize = texture.getSize();
		//std::cout << "Texture Size: " << textureSize.x << " x " << textureSize.y << std::endl;
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(objectSprite);
	}

	//returns objects size, or bounds (same thing? prolly not, technically but bah humbug)
	sf::FloatRect getGlobalBounds() const {
		return objectSprite.getGlobalBounds();
	}

private:
	sf::Texture texture;
	sf::Sprite objectSprite;
	std::string png;
	float x = 0;
	float y = 0;
};

