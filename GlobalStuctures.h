#pragma once
#include<SFML/Graphics.hpp>
#include "GameConfigs.h"
#include "Assets.h"

enum Axis { Vertical, Horizontal };

Tag* AllCollectables[COLLECTIBLES_N] = {
	&Tag(&redApple,RedApple),
	& Tag(&greenApple,GreenApple),
	& Tag(&goldenApple,GoldenApple),
	& Tag(&cherry,Cherry),
};

Tag* AllMovingObs[] = {
	&Tag(&rock,Rock),
	& Tag(&shuriken,Shuriken), };

Tag* world[HEIGHT_TILES_MAX][WIDTH_TILES_MAX];
std::vector<std::pair<int, int>> emptyTiles;