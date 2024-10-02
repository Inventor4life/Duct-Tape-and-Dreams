#pragma once

#include "mainheader.h"
#include "Object.h"


/*REMINDER TO SELF :
	put all physics related vars, such as gravity, ground, etc in a seperate class
 dedicated to giving and setting those variables.
*/
class Entity
{
public:
	Entity() {
		if (!texture.loadFromFile("Entities/playerSCP.png")) {
			std::cout << "no player png found";
		}
		entitySprite.setTexture(texture);
		ground = 700.f;
		entitySprite.setPosition(200.f, ground);
		jumpSpeed = -15.f;
		gravity = (981.0f*3);
		inAir = false;
		velocity = 0.f;
		jumpHeight = 400;
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

	//collision function so I dont gotta repeat this nonsense
	int collision(Object& object, float deltaTime,sf::Vector2f movement) {

		//Collision logic with OBJECTS, not window borders:
		sf::FloatRect entityB = entitySprite.getGlobalBounds();
		sf::FloatRect objectB = object.getGlobalBounds();
		int colliding = 0;
		//int onTop = 1;

		if (entityB.intersects(objectB)) {
			//if the entities current pos insersects the object:
			//checking if entity is dropping ONTO object. jumping on it, or the ground!
			//okay for somering FloatRect doesnt have right and bottom by default, so i gotta add those??
			colliding = 1;
			//collision from top
			if (entityB.top + entityB.height <= objectB.top + (velocity * deltaTime)) {
				// This means the player is above the object and falling down onto it
				movement.y = 0; // stop downward movement
				entitySprite.setPosition(entitySprite.getPosition().x, objectB.top - entityB.height);
				inAir = false; // Player is no longer in the air
			}
		
			//collision from bottom
			else if (entityB.top <= objectB.top + objectB.height && entityB.left > objectB.left && (entityB.left + entityB.width) < (objectB.left + objectB.width)) {
				movement.y = 0;
				entitySprite.setPosition(entitySprite.getPosition().x, (objectB.top + objectB.height) - entityB.height);
			}


			// collision from left
			else if (entityB.left < objectB.left && entityB.left + entityB.width >= objectB.left) {
				movement.x = 0;
				entitySprite.setPosition(objectB.left - 80, entitySprite.getPosition().y);
			}

			// collision from right
			else if (entityB.left + entityB.width > (objectB.left + objectB.width) && entityB.left < objectB.left + objectB.width) {
				movement.x = 0;
				entitySprite.setPosition((objectB.left + objectB.width), entitySprite.getPosition().y);
			}

		}
		//ensuring player character continues to fall if it walks off of the object, instead of getting stuck midair
		//but, ONLY if the player is currently ontop of the object
		if (entityB.top + entityB.height <= objectB.top + (velocity * deltaTime)) {
			if (entityB.left + entityB.width < objectB.left || entityB.left >(objectB.left + objectB.width)) {
				inAir = true;
			}
		}
		if(colliding){
			entitySprite.move(movement.x, movement.y);
			return 1;
		}
		if (!colliding) {
			return 0;
		}
	}




	void update(const sf::RenderWindow& window, float deltaTime, Object& object1, Object& object2) {
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
		
		//so this should work for each object, for for somereason it DOESNT. >.>
		// it DOES, just somewhat funky. not quite!
		// 
		int colliding = 0;
		//object 1, aka hatsune miku
		int c1 = collision(object1, deltaTime, movement);
		//object 2, aka platform 1
		int c2 = collision(object2, deltaTime, movement);
		//if not colliding with anything, move as normal
		if (c1 || c2) colliding = 1;
		if (!colliding) {
			entitySprite.move(movement.x, movement.y);
		}
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

