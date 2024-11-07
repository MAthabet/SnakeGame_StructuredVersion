#include "Generators.h"

void deleteLastGenerated(int i, int j)
{
	world[i][j]->sprite->setPosition(VOID_INDEX);
	world[i][j] = NULL;
}
void generate(Tag* assest, int i, int j, sf::Clock* clock = NULL, sf::Time time = sf::seconds(0))
{
	if (world[i][j])
		if (assest->type == world[i][j]->type)
		{
			deleteLastGenerated(i, j);
		}
	world[i][j] = assest;
	clock->restart();
	tileNotFree(i, j);
}
std::pair<int, int> generateEmptyTile()
{
	int x = emptyTiles.size();
	if (x < 1)
	{
		return { -1,-1 };
	}
	srand(10);
	int indx = rand() % emptyTiles.size();

	std::pair<int, int> genrated = emptyTiles[indx];

	return genrated;
}

void tileNotFree(int indx)
{
	emptyTiles[indx] = emptyTiles.back();

	emptyTiles.pop_back();
}

void tileNotFree(int i, int j)
{
	auto it = std::remove_if(emptyTiles.begin(), emptyTiles.end(),
		[i, j](const std::pair<int, int>& p) {
			return p.first == i && p.second == j;
		});
	if (it != emptyTiles.end())
	{
		emptyTiles.erase(it, emptyTiles.end());
	}
}

void DeleteTile(int i, int j)
{
	if (world[i][j])
	{
		world[i][j] = NULL;
	}
	tileIsEmpty({ i,j });
}