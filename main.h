#pragma once
#include "SFML/Graphics.hpp"
static int Score = 0;

char const Spritesheet_Path[] =".\\resources\\snake.png" ;
char const Resources_map[] = ".\\resources\\input.txt";

int const WIDTH_TILES_MAX = 40;
int const HEIGHT_TILES_MAX = 24;

//can not be less than 2
int const SNAKE_INIT_SIZE = 3;

//DO NOT CHANGE IT!!
int const PIXIL_L = 8;

int const TILE_L = 3;
int const TILE_SIZE = PIXIL_L * TILE_L;

int const GAME_W_MAX = WIDTH_TILES_MAX * TILE_SIZE;
int const GAME_H_MAX = HEIGHT_TILES_MAX * TILE_SIZE;

int const SCORE_H = 3;
int const GAMEwin_W_MAX = WIDTH_TILES_MAX * TILE_SIZE;
int const GAMEwin_H_MAX = (HEIGHT_TILES_MAX + SCORE_H) * TILE_SIZE;

int const GAME_SPEED = 7; //FPS
int const COLLECTIBLES_N = 4;
int const MOVING_OBSTACLES_N = 2;

float const APPLE_COOLDOWN_TIME = GAME_SPEED;
float const GOLDEN_APPLE_TIME = GAME_SPEED;
float const CHERRY_COOLDOWN_TIME = GAME_SPEED / 0.7;
float const CHERRY_TIME = GAME_SPEED / 1.25;

float const ROCK_COOLDOWN_TIME = GAME_SPEED * 1.5;
float const SHURIKEN_COOLDOWN_TIME = GAME_SPEED;

bool IsGameRunning = false;
int collectedApples = 0;

enum Axiss { Vertical, Horizontal };
enum Assets
{
	None, RedApple, Head, GreenApple, Body, Wall, RedObstacle, BlueObstacle, Rock,
	Shuriken, GoldenApple, Window, Cherry = 15
};

struct Tag
{
	sf::Sprite* sprite;
	Assets type;
	Tag(sf::Sprite* sprite,
		Assets type) : sprite(sprite), type(type) {};
};

sf::Texture spritesheet;

sf::IntRect headRect(4 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect headUpRect(1 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect headDownRect(3 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect headLeftRect(2 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect bodyRect(5 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect wallUPRect(10 * PIXIL_L, 2 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect wallLeftRect(9 * PIXIL_L, 2 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect wallRightRect(8 * PIXIL_L, 2 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect wallDownRect(7 * PIXIL_L, 2 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect wallRect(12 * PIXIL_L, 0 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect redObstacleRect(8 * PIXIL_L, 1 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect blueObstacleRect(8 * PIXIL_L, 0 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect rockRect(7 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect shurikenRect(6 * PIXIL_L, 6 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect redAppleRect(6 * PIXIL_L, 0 * PIXIL_L, PIXIL_L, PIXIL_L);;
sf::IntRect greenAppleRect(6 * PIXIL_L, 4 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect goldenAppleRect(6 * PIXIL_L, 1 * PIXIL_L, PIXIL_L, PIXIL_L);
sf::IntRect cherryRect(6 * PIXIL_L, 3 * PIXIL_L, PIXIL_L, PIXIL_L);

sf::Sprite head(spritesheet, headRect);
sf::Sprite headUp(spritesheet, headUpRect);
sf::Sprite headDown(spritesheet, headDownRect);
sf::Sprite headLeft(spritesheet, headLeftRect);
sf::Sprite body(spritesheet, bodyRect);
sf::Sprite wallUp(spritesheet, wallUPRect);
sf::Sprite wallLeft(spritesheet, wallLeftRect);
sf::Sprite wallRight(spritesheet, wallRightRect);
sf::Sprite wallDown(spritesheet, wallDownRect);
sf::Sprite wall(spritesheet, wallRect);
sf::Sprite redObstacle(spritesheet, redObstacleRect);
sf::Sprite blueObstacle(spritesheet, blueObstacleRect);
sf::Sprite rock(spritesheet, rockRect);
sf::Sprite shuriken(spritesheet, shurikenRect);
sf::Sprite redApple(spritesheet, redAppleRect);
sf::Sprite greenApple(spritesheet, greenAppleRect);
sf::Sprite goldenApple(spritesheet, goldenAppleRect);
sf::Sprite cherry(spritesheet, cherryRect);

void resizeAllAssets()
{
	int w, h;
	sf::Sprite* all[] =
	{
		&head,&headUp,&headDown,&headLeft,&body,&wallUp,&wallLeft,&wallRight,&wallDown,
		&redObstacle,&blueObstacle,&rock,&shuriken,&redApple,&greenApple,&goldenApple,&cherry,&wall
	};
	for (sf::Sprite* sprite : all)
	{
		w = sprite->getLocalBounds().width;
		h = sprite->getLocalBounds().height;
		sprite->setScale(
			TILE_SIZE / w,
			TILE_SIZE / h);
		sprite->setOrigin(w / 2, h / 2);
	}

}

void runGame(sf::RenderWindow* window);
void startGame(sf::RenderWindow* window);
void gameLoop(sf::RenderWindow* window);
void endGame();
void restartGame();
void openGameWin(sf::RenderWindow* window);
int loadSpritesheet();
void moveToVoid(Tag* pawn);
void moveAllObs(float speed = 1);
void flipAllCol(float speed = 1);
bool onScreen(Tag* assest);
void generateFood(sf::Clock* clock, sf::Time* time);
void generateApple(sf::Clock* clock, sf::Time* time);
void forceGenerateApple(sf::Clock* clock);
void generateGoldenApple();
void generateCherry();

void generateRock(sf::Clock* clock = NULL, sf::Time* time = NULL);
void generateShuriken(sf::Clock* clock = NULL, sf::Time* time = NULL);

sf::Vector2f const VOID_INDEX = { GAMEwin_H_MAX + 100, GAMEwin_W_MAX + 100 };

enum Direction { Up, Down, Left, Right };
std::pair<int, int> generateEmptyTile();

void generate(Tag* assest, int i, int j, sf::Clock* clock = NULL, sf::Time time = sf::seconds(0));

void tileNotFree(int indx);

void tileNotFree(int i, int j);
Tag redAppleTag(&redApple, RedApple);
Tag greenAppleTag(&greenApple, GreenApple);
Tag goldenAppleTag(&goldenApple, GoldenApple);
Tag cherryTag(&cherry, Cherry);

Tag rockTag(&rock, Rock);
Tag shurikenTag(&shuriken, Shuriken);

Tag* AllCollectables[] = {
	&redAppleTag,
	&greenAppleTag,
	&goldenAppleTag,
	&cherryTag,
};

Tag* AllMovingObs[] = {
	&rockTag,
	&shurikenTag
};

Tag* world[HEIGHT_TILES_MAX][WIDTH_TILES_MAX];
std::vector<std::pair<int, int>> emptyTiles;
bool checkSelfCollision();
bool checkSnakeCollision();
bool checkCollisionWithWindow(int x, int y);
bool checkCollision(Tag* spawn);
bool IsInverted = false;

void handleSnakeInput();
void invertSnakeInput();

int snakeHealth = 2;
bool snakeShielded = false;
bool invertedInput = false;
bool snakeCollidedWithWin = false;
bool snakeHasEatenApple = true;

bool snakeAlive = true;
int speed;
Direction lastInput = Direction::Right;
std::vector<sf::Sprite> snake;
sf::Vector2i direction;
sf::Vector2f tailStartPosition;
Tag* snakeColidedWith = NULL;

void drawSnake(sf::RenderWindow* win);
bool checkSnakeCollision();
void initSnake(int snakeLength, sf::Vector2i start);
void moveSnake();
void setStartPosition(sf::Vector2f startPosition);

void handleSnakeCollisionWithWindow();
void handleSnakeCollisionWithCollectable();
void handleSnakeCollisionWithMovingObstacle();
void handleSnakeCollisionWithStationryObstacle();
void handleSnakeCollisionWithWall();
void handleSnakeDeath();
void updateSnakeDirection();
void growSnake();
void shrinkSnake();
void deleteFromScreen(Tag* asset);

void moveAndRotate(sf::Sprite* assest, Axiss axis, float linSpeed = 1, float rotSpeed = 30)
{
	int y = assest->getPosition().y;
	int x = assest->getPosition().x;

	if (axis == Vertical)
	{
		int Newy = y + TILE_SIZE * linSpeed;
		assest->setPosition(x, Newy);
		assest->rotate(rotSpeed);
	}
	else
	{
		int Newx = x + TILE_SIZE * linSpeed;
		assest->setPosition(Newx, y);
		assest->rotate(rotSpeed);
	}

}

sf::Vector2i PlayerTailStart;
void drawMap(sf::RenderWindow* window);
void deleteMap();
sf::Vector2i fileToArray(std::string s);
void tileIsEmpty(std::pair<int, int> position);
void SpritetoWall(sf::Sprite* temp, int i, int j);
void setPlayerTailStart(int i, int j);


