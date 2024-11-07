#include "Game.h"
#include "Assets.h"
#include "GlobalStuctures.h"
#include "Snake.h"
#include "SnakeInput.h"
#include "Map.h"
#include "Generators.h"
#include "Include.h"

void runGame(sf::RenderWindow* window)
{
    startGame(window);
    gameLoop(window);
    endGame();
}

void startGame(sf::RenderWindow* window)
{
    sf::Vector2f snakeTail;
    loadSpritesheet();
    resizeAllAssets();
    openGameWin(window);
    snakeTail = fileToArray(Resources_map);
    //here
    initSnake(SNAKE_INIT_SIZE, snakeTail);
    IsGameRunning = true;
}
void gameLoop(sf::RenderWindow* window)
{
    sf::Clock foodClock;
    sf::Time foodTime = sf::seconds(APPLE_COOLDOWN_TIME);

    sf::Clock goldenAppleClock;
    sf::Time goldenAppleTime = sf::seconds(GOLDEN_APPLE_TIME);

    sf::Clock cherryClock;
    sf::Time cherryCoolDownTime = sf::seconds(CHERRY_COOLDOWN_TIME);
    sf::Time cherryLife = sf::seconds(CHERRY_TIME);

    sf::Clock ShurikenClock;
    sf::Time ShurikenTime = sf::seconds(SHURIKEN_COOLDOWN_TIME);
    sf::Clock RockClock;
    sf::Time RockTime = sf::seconds(ROCK_COOLDOWN_TIME);
    bool IsGameRunning = false;

    while (IsGameRunning && window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (invertedInput)
            handleSnakeInput();
        else
            invertSnakeInput();

        moveSnake();
        moveAllObs();
        flipAllCol();

        generateFood(&foodClock,&foodTime);

        if (onScreen(AllCollectables[2]))
        {
            if( goldenAppleClock.getElapsedTime() > goldenAppleTime)
                deleteFromScreen(AllCollectables[2]);
        }
        else if ((collectedApples + 1) % 10 == 0)
        {
            generateGoldenApple();
            goldenAppleClock.restart();
        }


        if (cherryClock.getElapsedTime() > cherryCoolDownTime)
        {
            generateCherry();
            cherryClock.restart();
        }
        else if (cherryClock.getElapsedTime() > cherryLife)
        {
            deleteFromScreen(AllCollectables[3]);
        }

        generateRock(&RockClock, &RockTime);
        generateShuriken(&ShurikenClock, &ShurikenTime);


        checkSelfCollision();
        checkSnakeCollision();
        // Clear the screen
        window->clear();

        drawMap(window);

        if (snakeAlive)
        {
            drawSnake(window);
        }
        window->display();
    }
}
void endGame()
{
    IsGameRunning = false;
    deleteMap();
}
void restartGame()
{
    IsGameRunning = true;
}
void openGameWin(sf::RenderWindow* window)
{
    window->create(sf::VideoMode(GAMEwin_W_MAX, GAMEwin_H_MAX), "Snake Game");
    window->setFramerateLimit(GAME_SPEED);
}
int loadSpritesheet()
{
    if (!spritesheet.loadFromFile(Spritesheet_Path))
    {
        return -1;
    }
}
void handleSnakeDeath()
{
    IsGameRunning = false;
}

void moveAllObs(float speed = 1)
{
    for (int i = 0; i < MOVING_OBSTACLES_N; i++)
    {
        moveAndRotate(AllMovingObs[i].first, AllMovingObs[i].second);
    }
}
void flipAllCol(float speed = 1)
{
    for (int i = 0; i < COLLECTIBLES_N; i++)
    {
        AllCollectables[i]->sprite->setScale(
            -speed * AllCollectables[i]->sprite->getScale().x,
            AllCollectables[i]->sprite->getScale().y);
    }
}

void generateFood(sf::Clock* clock, sf::Time* time)
{
        if (snakeHasEatenApple)
        {
            snakeHasEatenApple = false;
            forceGenerateApple(clock);
        }
        if (snakeColidedWith) //Null Guard
        {
            generateApple(clock, time);
            snakeHasEatenApple = false;
        }
        else if ((collectedApples + 1) % 5 != 0 && (snakeColidedWith->type == Assets::RedApple || snakeColidedWith->type == Assets::GreenApple))
        {
            generateApple(clock, time);
            snakeHasEatenApple = false;
        }
}
void generateApple(sf::Clock* clock, sf::Time* time)
{
    std::pair<int, int> rand = generateEmptyTile();
    if (((collectedApples + 1) % 4) == 0)
    {
        generate(AllCollectables[1], rand.first, rand.second, &clock, *time);
    }
    else
        generate(AllCollectables[0], rand.first, rand.second);
}
void forceGenerateApple(sf::Clock* clock)
{
    std::pair<int, int> rand = generateEmptyTile();
    if (((collectedApples + 1) % 4) == 0)
    {
        generate(AllCollectables[1], rand.first, rand.second);
    }
    else
        generate(AllCollectables[0], rand.first, rand.second);
}
void generateGoldenApple()
{
    std::pair<int, int> rand = generateEmptyTile();
    generate(AllCollectables[2], rand.first, rand.second);
}
void generateCherry()
{
    srand(time(0));
    int rndm = rand() % 101;
    if (rndm < 11)
    {
        std::pair<int, int> rand = generateEmptyTile();
        generate(AllCollectables[3], rand.first, rand.second);
    }
}

void generateRock()
{
    std::pair<int, int> rand = generateEmptyTile();
    generate(AllMovingObs[0], 0, rand.second);
}
void generateShuriken()
{
    srand(time(0));
    int rndm = rand() % HEIGHT_TILES_MAX;
    return generate(AllMovingObs[1], rndm, 0);
}
bool onScreen(Tag* assest)
{
    int y = assest->sprite->getPosition().y;
    int x = assest->sprite->getPosition().x;
    if (world[y][x]->type == assest->type)
        return true;
    return false;
}
void deleteFromScreen(Tag* asset)
{
    int y = asset->sprite->getPosition().y;
    int x = asset->sprite->getPosition().x;
    if (world[y][x]->type == asset->type)
        world[y][x] = NULL;
    asset->sprite->setPosition(VOID_INDEX);
}