#pragma once
#include "GlobalStuctures.h"
#include "Map.h"
std::pair<int, int> generateEmptyTile();

void generate(Tag* assest, int i, int j, sf::Clock* clock = NULL, sf::Time time = sf::seconds(0));

void tileNotFree(int indx);

void tileNotFree(int i, int j);

void DeleteTile(int i, int j);