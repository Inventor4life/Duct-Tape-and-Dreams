#include "mainheader.h"

int main(int argc, char* argv[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);
	//lua.script("print('bark bark bark!')");

    //creates initial window, with resolution.
	sf::Window window(sf::VideoMode(1920, 1080), "game test", sf::Style::Default);
    window.setFramerateLimit(60);

    //keeps window open, as well as opening it in the first place.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }




	return 0;// end return 0;
}