#pragma once
#include "Include.h"

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
void initSnake(int snakeLength, sf::Vector2f start);
void moveSnake();
void setStartPosition(sf::Vector2f startPosition);

void handleSnakeDeath();
void handleSnakeCollisionWithWindow();
void handleSnakeCollisionWithCollectable();
void handleSnakeCollisionWithMovingObstacle();
void handleSnakeCollisionWithStationryObstacle();
void handleSnakeCollisionWithWall();

void updateSnakeDirection();
void growSnake();
void shrinkSnake();