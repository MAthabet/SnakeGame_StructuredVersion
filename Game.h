#pragma once
#include <SFML/Graphics.hpp>
#include "GameConfigs.h"

bool IsGameRunning = false;
int collectedApples = 0;
Tag* snakeColidedWith;

void runGame(sf::RenderWindow* window);
void startGame(sf::RenderWindow* window);
void gameLoop(sf::RenderWindow* window);
void endGame();
void restartGame();
void openGameWin(sf::RenderWindow& window);
int loadSpritesheet();
void handleSnakeDeath();

void moveAllObs(float speed = 1);
void flipAllCol(float speed = 1);

void generateFood(sf::Clock* clock, sf::Time* time);
void generateApple(sf::Clock* clock, sf::Time* time);
void forceGenerateApple(sf::Clock* clock);
void generateGoldenApple();
void generateCherry();

void generateRock(sf::Clock* clock, sf::Time* time);
void generateShuriken(sf::Clock* clock, sf::Time* time);
