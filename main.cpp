#include <iostream>
#include <SFML/Graphics.hpp>
#include "Include.h"

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(GAMEwin_W_MAX, GAMEwin_H_MAX), "Snake Game Strucured");
    window.setFramerateLimit(GAME_SPEED);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        runGame(&window);
        break;
    }

    return 0;
}