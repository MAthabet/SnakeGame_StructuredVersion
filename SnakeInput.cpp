#include "SnakeInput.h"
#include <SFML/Graphics.hpp>

void handleSnakeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.lastInput != Direction::Down)
        player.lastInput = Direction::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.lastInput != Direction::Up)
        player.lastInput = Direction::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.lastInput != Direction::Left)
        player.lastInput = Direction::Right;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.lastInput != Direction::Right)
        player.lastInput = Direction::Left;
}
void invertSnakeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.lastInput != Direction::Up)
        player.lastInput = Direction::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.lastInput != Direction::Down)
        player.lastInput = Direction::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.lastInput != Direction::Right)
        player.lastInput = Direction::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.lastInput != Direction::Left)
        player.lastInput = Direction::Right;
}