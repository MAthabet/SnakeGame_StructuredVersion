#pragma once
#include <SFML/Graphics.hpp>
sf::Vector2i PlayerTailStart;
void drawMap(sf::RenderWindow* window);
void deleteMap();
sf::Vector2i fileToArray(std::string s);
void tileIsEmpty(std::pair<int, int> position);
void SpritetoWall(sf::Sprite* temp, int i, int j);
void setPlayerTailStart(int i, int j);
void DeleteTile(int i, int j);
void tileNotFree(int indx)
{
	emptyTiles[indx] = emptyTiles.back();

	emptyTiles.pop_back();
}