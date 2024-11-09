#pragma once
#include "mainheader.h"
#include "Physics.h"
class Entity : private Physics
{
public:
	Entity(string path, sf::Vector2f spawnLocation, float jumpS, float jumpH, string controller) {
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

	void processEvents(sf::Keyboard::Key key, bool isPressed) {
		//std::cout << "frame: " << frame;
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
			setVelocity(-sqrtf(2.0f * getGravity() * jumpHeight));
		}
		if (key == sf::Keyboard::E) {
			system("pause");
		}
		//frame++;
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
			//printf("inAir\n");
			setVelocity(getVelocity() + getGravity() * deltaTime);
			movement.y += getVelocity() * deltaTime;
			//jumping and gravity! god help us
			if (position.y + movement.y >= getGround()) {
				entitySprite.setPosition(position.x, getGround());
				setVelocity(0);
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

