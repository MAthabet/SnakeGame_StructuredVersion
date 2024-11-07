#include "Map.h"
#include "GameConfigs.h"
#include "GlobalStuctures.h"
#include <fstream> 

void drawMap(sf::RenderWindow* window)
{
	if (window)
	{
		for (int i = 0; i < HEIGHT_TILES_MAX;i++)
		{
			for (int j = 0; j < WIDTH_TILES_MAX; j++)
			{
				if (world[i][j])
					if(world[i][j]->sprite)
					window->draw(*(world[i][j])->sprite);
			}
		}
	}
}

void deleteMap()
{
	for (int i = 0; i < HEIGHT_TILES_MAX;i++)
	{
		for (int j = 0; j < HEIGHT_TILES_MAX; j++)
		{
			if (world[i][j])
				delete world[i][j];
		}
	}
}
sf::Vector2i fileToArray(std::string s)
{
	sf::Vector2i snakeTail(GAME_H_MAX/2, GAME_W_MAX / 2); // defult start mid map
	std::string line;
	std::ifstream file(s);
	if (!file.is_open()) {
		std::ofstream outFile(s, std::ios::app);
	}
	char c;
	for (int i = 0; i < HEIGHT_TILES_MAX;i++)
	{
		bool isThereChar = true;

		if (!std::getline(file, line))
		{
			isThereChar = false;
		}
		int size = line.size();
		for (int j = 0; j < WIDTH_TILES_MAX; j++)
		{
			if (isThereChar)
			{
				c = line[j];
				sf::Sprite* temp = (new sf::Sprite());
				Assets type = None;
				switch (c)
				{
				case '\0':
					emptyTiles.push_back({ i,j });
					isThereChar = false;
					break;
				case 'w':
				case 'W':
					SpritetoWall(temp, i, j);
					type = Wall;
					break;
				case 'r':
				case 'R':
					*temp = redObstacle;
					type = RedObstacle;
					break;
				case 'b':
				case 'B':
					*temp = blueObstacle;
					type = BlueObstacle;
					break;
				case 's':
				case 'S':
				{
					snakeTail = { i, j };
					for (int k = 0; k < SNAKE_INIT_SIZE; k++)
					{
						emptyTiles.push_back({ i,j });
						j++;
					}
					if (j > size)
						isThereChar = false;
					delete temp;
					break;
				}
				default:
					emptyTiles.push_back({ i,j });
					break;
				}
				if (type != None)
				{
					temp->setPosition(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
					world[i][j] = new Tag(temp, type);
				}
			}
			else emptyTiles.push_back(std::make_pair(i, j));
		}
	}
	return snakeTail;
}
void tileIsEmpty(std::pair<int, int> position)
{
	emptyTiles.push_back(position);
}
void SpritetoWall(sf::Sprite* temp, int i, int j)
{
	if (i == 0)
	{
		*temp = wallUp;
	}
	else if (i == WIDTH_TILES_MAX - 1)
	{
		*temp = wallDown;
	}
	else if (j == 0)
	{
		*temp = wallLeft;
	}
	else if (j == WIDTH_TILES_MAX - 1)
	{
		*temp = wallRight;
	}
	else *temp = wall;
}
void setPlayerTailStart(int i, int j)
{
	PlayerTailStart = { j * TILE_SIZE + +TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2 };
}

void DeleteTile(int i, int j)
{
	if (i >= 0 && i < HEIGHT_TILES_MAX)
		if (j >= 0 && j < WIDTH_TILES_MAX)
		{
			world[i][j] = NULL;
			tileIsEmpty({ i,j });
		}
}