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
		gravity = 0.25f;
		inAir = false;
		ground = 600.f;
		velocity = 0.f;
	}



	void processEvents(sf::Keyboard::Key key, bool isPressed) {

		if (key == sf::Keyboard::W) {up = isPressed;}
		if (key == sf::Keyboard::S) {down = isPressed;}
		if (key == sf::Keyboard::A) {
			left = isPressed;
		}
		if (key == sf::Keyboard::D) {
			right = isPressed;
		}
		if (key == sf::Keyboard::Space && !inAir) {
			inAir = true;
			velocity = jumpSpeed;
		}
	}

	void update(const sf::RenderWindow& window) {
		//float movement = 0.f;
		float speed = 0.4f; // changes speed of sprite (ITS REALLY FAST FOR SOME REASON)
		sf::Vector2f movement(0.f, 0.f);

		if (up) movement.y -= speed;
		if (down) movement.y += speed;
		if (left) movement.x -= speed;
		if (right) movement.x += speed;

		//prevents moving out of bounds
		sf::Vector2f position = entitySprite.getPosition();
		if (position.x + movement.x < 0) {
			movement.x = -position.x; //stops movement at 
		}
		else if (position.x + movement.x + entitySprite.getGlobalBounds().width > window.getSize().x) {
			movement.x = window.getSize().x - (position.x + entitySprite.getGlobalBounds().width); // Prevent moving out on the right
		}
		else if (position.y + movement.y < 0) {
			movement.y = -position.y;
		}
		else if (position.y + movement.y + entitySprite.getGlobalBounds().width > window.getSize().y) {
			movement.y = window.getSize().y - (position.y + entitySprite.getGlobalBounds().width);
		}


		/* SHELVING JUMPING AT THE MOMENT ITS A BIT HARD >:(
		if (inAir) {
			//jumping and gravity! god help us
			velocity += gravity; //increase velocity over time based on gravity
			entitySprite.move(movement); //horrible variables names im noticing, will change later

			if (entitySprite.getPosition().y >= ground) {
				entitySprite.setPosition(position.x, ground);
				velocity = 0; //has stopped moving, no longer jumping
				inAir = false;
			}
		}
		*/
		
		entitySprite.move(movement);
		
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
	float jumpSpeed;
	float gravity;
	float velocity;
	float ground;

};

