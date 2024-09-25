#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "mainheader.h"
#include <iostream>
class Entity
{
public:
	Entity() {
		if (!texture.loadFromFile("playerSCP.png")) {
			std::cout << "no player png found";
		}
		entitySprite.setTexture(texture);
		entitySprite.setPosition(200.f, 600.f);
		jumpSpeed = -15.f;
		gravity = (981.0f*3);
		inAir = false;
		ground = 600.f;
		velocity = 0.f;
		jumpHeight = 100;
	}



	void processEvents(sf::Keyboard::Key key, bool isPressed) {

		//if (key == sf::Keyboard::W) {up = isPressed;}
		//if (key == sf::Keyboard::S) {down = isPressed;}
		if (key == sf::Keyboard::A) {
			left = isPressed;
		}
		if (key == sf::Keyboard::D) {
			right = isPressed;
		}
		if (key == sf::Keyboard::Space && !inAir) {
			inAir = true;
			//velocity jump formula is: sqrt(2.0f gravity * jumpHeight)
			velocity = -sqrtf(2.0f * gravity * jumpHeight);

		}
	}

	void update(const sf::RenderWindow& window, float deltaTime) {
		//float movement = 0.f;
		float speed = 1000.f; // changes speed of sprite (ITS REALLY FAST FOR SOME REASON)
		sf::Vector2f movement(0.f, 0.f);
		//velocity = 0.f; 

		//if (up) movement.y -= speed;
		//if (down) movement.y += speed;
		if (left) movement.x -= (speed * deltaTime);
		if (right) movement.x += (speed * deltaTime);

		/* SHELVING JUMPING AT THE MOMENT ITS A BIT HARD >:(
		 AAAAND SHELVING IS BACK because we doing terraria now ;-; */

		sf::Vector2f position = entitySprite.getPosition();
		if (inAir) {
			velocity += gravity * deltaTime;
			movement.y += velocity * deltaTime;
			//jumping and gravity! god help us
			//velocity += gravity; //increase velocity over time based on gravity

		//position = entitySprite.getPosition();
			if (position.y + movement.y >= ground) {
				entitySprite.setPosition(position.x, ground);
				velocity = 0;
				inAir = false;
			}
		}
		//prevents moving out of bounds
		position = entitySprite.getPosition();
		if (position.x + movement.x < 0) {
			movement.x = -position.x; //stops movement at 
		}
		else if (position.x + movement.x + entitySprite.getGlobalBounds().width > window.getSize().x) {
			movement.x = window.getSize().x - (position.x + entitySprite.getGlobalBounds().width); // Prevent moving out on the right
		}

		entitySprite.move(movement.x, movement.y);
		
		//entitySprite.move(movement.x, movement.y);
	}


	void drawTo(sf::RenderWindow &window) {
		window.draw(entitySprite);
	}

private:

	sf::Texture texture;  
	sf::Sprite entitySprite;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool inAir = false;
	//for jumping, we need a buncha fancy shit
	float jumpHeight;
	float jumpSpeed;
	float gravity;
	float velocity;
	float ground;

};

