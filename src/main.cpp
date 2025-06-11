#include <iostream>

#include <sol/sol.hpp>
#include <steam/steam_api.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

int main()
{
	// Verify SFML installation
	// Create a window
	auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	
    // Create a circle
    sf::CircleShape circle(50.f); // Radius of 50
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2(200.f, 200.f)); // Center of the circle
	
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();
		
		window.draw(circle);
		
		window.display();
	}
	
	
	// Verify SteamAPI installation
	if(!SteamAPI_Init()) {
	return -1;
	}
	SteamAPI_Shutdown();


	// Verify sol2/Lua/LuaJIT installation
	sol::state lua;
	lua.open_libraries(sol::lib::jit, sol::lib::base);
	lua.script("print(jit.version)");


	//Ignore this mess, it's used to verify box2d installation.
	std::cout << std::endl; // Separate Luajit output from box2d output
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
	b2WorldId worldId = b2CreateWorld(&worldDef);
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2{ 0.0f, 4.0f };
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	groundBodyDef.position = b2Vec2{ 0.0f, -10.0f };
	b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
	b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
	b2ShapeDef groundShapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
	b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
	float timeStep = 1.0f / 60.0f;
	int subStepCount = 4;
	for (int i = 0; i < 90; ++i)
	{
		b2World_Step(worldId, timeStep, subStepCount);
		b2Vec2 position = b2Body_GetPosition(bodyId);
		b2Rot rotation = b2Body_GetRotation(bodyId);
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
	}
	b2DestroyWorld(worldId);
	
	return 0;
}
