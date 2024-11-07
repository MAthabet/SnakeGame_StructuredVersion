#include "Main.h"
#include <fstream>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(GAMEwin_W_MAX, GAMEwin_H_MAX), "Snake Game Strucured");
    window.setFramerateLimit(GAME_SPEED);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        runGame(&window);
        break;
    }

    return 0;
}

void DeleteTile(float i, float j)
{
    if (world[(int)i][(int)j])
    {
        world[(int)i][(int)j] = NULL;
    }
    tileIsEmpty({ (int)i,(int)j });
}
bool checkSelfCollision()
{
    int x = snake[0].getPosition().x;
    int y = snake[0].getPosition().y;
    for (int i = snake.size() - 1; i > 0;i--)
    {
        if (x == snake[i].getPosition().x)
            if (y == snake[i].getPosition().y)
            {
                handleSnakeDeath();
                return true;
            }
    }
    
}
bool checkSnakeCollision()
{
    bool isColided = false;
    int j = snake[0].getPosition().x / TILE_SIZE;
    int i = snake[0].getPosition().y / TILE_SIZE;

    //jumping over wall bug
    if (snakeCollidedWithWin)
    {
        snakeCollidedWithWin = false;
        if (j >= WIDTH_TILES_MAX) j = 0;
        else if (j <= 0) j = WIDTH_TILES_MAX - 1;
        else if (i >= HEIGHT_TILES_MAX) i = 0;
        else if (i <= 0) i = HEIGHT_TILES_MAX - 1;
        goto second_check;
    }
    if (checkCollisionWithWindow(j, i))
    {
        handleSnakeCollisionWithWindow();
        checkSnakeCollision();
        return true;
    }
second_check:
    Assets current;
    if (world[i][j])
    {
        current = world[i][j]->type;
        if (world[i][j])
            snakeColidedWith = world[i][j];
        switch (current)
        {
        case Wall:
            handleSnakeCollisionWithWall();
            isColided = true;
            break;
        case RedObstacle:
        case BlueObstacle:
            handleSnakeCollisionWithStationryObstacle();
            isColided = true;
            break;
        case RedApple:
        case GreenApple:
        case GoldenApple:
        case Cherry:
            handleSnakeCollisionWithCollectable();
            isColided = true;
            break;
        default:
            break;
        }
    }
    return isColided;
}
bool checkCollision(Tag* pawn)
{
    bool isColided = false;

    int j = pawn->sprite->getPosition().x / TILE_SIZE;
    int i = pawn->sprite->getPosition().y / TILE_SIZE;
    Assets current;
    if (world[i][j])
    {
        current = world[i][j]->type;
        switch (current)
        {
        case Wall:
            moveToVoid(pawn);
            isColided = true;
            break;
        case RedObstacle:
        case BlueObstacle:
            moveToVoid(pawn);
            isColided = true;
            break;
        case RedApple:
        case GreenApple:
        case GoldenApple:
        case Cherry:
            DeleteTile(i, j);
            isColided = true;
            break;
        default:
            break;
        }
    }
    return isColided;
}
bool checkCollisionWithWindow(int x, int y)
{
    if (x >= GAME_W_MAX || x <= 0)
        return true;
    if (y >= GAME_H_MAX || y <= 0)
        return true;
    return false;
}
void moveToVoid(Tag* pawn)
{
    pawn->sprite->setPosition(GAMEwin_W_MAX + 100, GAMEwin_H_MAX + 100);
}

void runGame(sf::RenderWindow* window)
{
    startGame(window);
    gameLoop(window);
    endGame();
}

void startGame(sf::RenderWindow* window)
{
    sf::Vector2i snakeTail;
    loadSpritesheet();
    resizeAllAssets();
    openGameWin(window);
    fileToArray(Resources_map);
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

    while (IsGameRunning && window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (!invertedInput)
            handleSnakeInput();
        else
            invertSnakeInput();

        moveSnake();
        moveAllObs();
        flipAllCol();

        generateFood(&foodClock, &foodTime);

        if (onScreen(AllCollectables[2]))
        {
            if (goldenAppleClock.getElapsedTime() > goldenAppleTime)
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

void moveAllObs(float speed)
{
    moveAndRotate(AllMovingObs[0]->sprite, Axiss::Vertical);
    moveAndRotate(AllMovingObs[1]->sprite, Axiss::Horizontal);
}
void flipAllCol(float speed)
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
    if (!snakeColidedWith) //Null Guard
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
        generate(AllCollectables[1], rand.first, rand.second, clock, *time);
    }
    else
        generate(AllCollectables[0], rand.first, rand.second, clock, *time);
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

void generateRock(sf::Clock* clock, sf::Time* time)
{
    std::pair<int, int> rand = generateEmptyTile();
    generate(AllMovingObs[0], 0, rand.second);
}
void generateShuriken(sf::Clock* clock, sf::Time* time)
{
    srand(0);
    int rndm = rand() % HEIGHT_TILES_MAX;
    return generate(AllMovingObs[1], rndm, 0);
}
bool onScreen(Tag* assest)
{
    int y = assest->sprite->getPosition().y;
    int x = assest->sprite->getPosition().x;
    if(world[y][x])
    if (world[y][x]->type == assest->type)
        return true;
    return false;
}
void deleteFromScreen(Tag* asset)
{
    int y = asset->sprite->getPosition().y;
    int x = asset->sprite->getPosition().x;
    if (y < WIDTH_TILES_MAX && y >= 0 && x < HEIGHT_TILES_MAX && x >= 0)
        if(world[y][x])
            if (world[y][x]->type == asset->type)
                world[y][x] = NULL;
    asset->sprite->setPosition(VOID_INDEX);
}

void deleteLastGenerated(int i, int j)
{
    world[i][j]->sprite->setPosition(VOID_INDEX);
    world[i][j] = NULL;
}
void generate(Tag* assest, int i, int j, sf::Clock* clock, sf::Time time)
{
    if (world[i][j])
        if (assest->type == world[i][j]->type)
        {
            deleteLastGenerated(i, j);
        }
    world[i][j] = assest;
    if(clock)
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



void drawMap(sf::RenderWindow* window)
{
    if (window)
    {
        for (int i = 0; i < HEIGHT_TILES_MAX;i++)
        {
            for (int j = 0; j < WIDTH_TILES_MAX; j++)
            {
                if (world[i][j])
                    if (world[i][j]->sprite)
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
    sf::Vector2i snakeTail(GAME_H_MAX / 2, GAME_W_MAX / 2); // defult start mid map
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


void drawSnake(sf::RenderWindow* win)
{
    for (auto& spirit : snake)
    {
        win->draw(spirit);
    }
}

void initSnake(int snakeLength, sf::Vector2i start)
{
    head.setPosition({ (float)start.x * TILE_SIZE + +TILE_SIZE / 2,(float)start.y * TILE_SIZE + TILE_SIZE / 2 });
    snake.push_back(head);
    for (int i = 1; i < snakeLength; i++)
    {
        body.setPosition(tailStartPosition);
        snake.push_back(body);
        moveSnake();
    }
}
void moveSnake()
{
    for (int i = snake.size() - 1; i > 0; i--)
    {
        snake[i].setPosition(snake[i - 1].getPosition());
    }
    sf::Sprite temp = snake[0];
    updateSnakeDirection();
    snake[0].setPosition(temp.getPosition().x + direction.x * TILE_SIZE, direction.y * TILE_SIZE + temp.getPosition().y);
}
void growSnake()
{
    sf::Sprite sprite = snake.back();
    snakeHealth++;
    snake.push_back(sprite);
}
void shrinkSnake()
{
    if (snakeHealth < 1)
    {
        handleSnakeDeath();
        return;
    }
    snakeHealth--;
    snake.pop_back();
}

void setStartPosition(sf::Vector2f startPosition)
{
    tailStartPosition = startPosition;
}
void updateSnakeDirection()
{
    switch (lastInput)
    {
    case Direction::Up:
        direction = { 0,-1 };
        snake[0] = headUp;
        break;
    case Direction::Down:
        direction = { 0,1 };
        snake[0] = headDown;
        break;
    case Direction::Left:
        direction = { -1,0 };
        snake[0] = headLeft;
        break;
    case Direction::Right:
        direction = { 1,0 };
        snake[0] = head;
        break;
    default:
        break;
    }
}

void handleSnakeCollisionWithWindow()
{
    int x = snake[0].getPosition().x;
    int y = snake[0].getPosition().y;
    if (x >= GAME_W_MAX)
        snake[0].setPosition(0 + TILE_SIZE / 2, y);
    else if (x <= 0)
        snake[0].setPosition(GAME_W_MAX + TILE_SIZE / 2, y);
    else if (y <= 0)
        snake[0].setPosition(x, GAME_H_MAX + TILE_SIZE / 2);
    else if (y >= GAME_H_MAX)
        snake[0].setPosition(x, 0 + TILE_SIZE / 2);
    snakeCollidedWithWin = true;
}
void handleSnakeCollisionWithCollectable()
{
    switch (snakeColidedWith->type)
    {
    case RedApple:
    case GreenApple:
        Score += snakeColidedWith->type * 10;
        collectedApples++;
        snakeHasEatenApple = true;
        printf("%d", collectedApples);
        growSnake();
        break;
    case GoldenApple:
        snakeShielded = true;
        Score += GoldenApple * 10;
        collectedApples++;
        break;
    case Cherry:
        Score += Cherry * 10;
        IsInverted = false;
        break;
    default:
        break;
    }
    DeleteTile(snakeColidedWith->sprite->getPosition().x / TILE_SIZE, snakeColidedWith->sprite->getPosition().y / TILE_SIZE);
}
void handleSnakeCollisionWithMovingObstacle()
{
    if (!snakeShielded)
    {
        switch (snakeColidedWith->type)
        {
        case Rock:
            IsInverted = false;
            break;
        case Shuriken:
            //TODO : cut();
            shrinkSnake();
            break;
        default:
            break;
        }
        DeleteTile(snakeColidedWith->sprite->getPosition().x / TILE_SIZE, snakeColidedWith->sprite->getPosition().y / TILE_SIZE);
    }
}
void handleSnakeCollisionWithStationryObstacle()
{
    if (!snakeShielded)
        switch (snakeColidedWith->type)
        {
        case Wall:
            handleSnakeDeath();
            break;
        case RedObstacle:
        {
            int temp = direction.x;
            direction.x = direction.y;
            direction.y = temp;
            goto exit;
        }
        break;
        case BlueObstacle:
            shrinkSnake();
            goto exit;
            break;
        default:
            break;
        }
    DeleteTile(snakeColidedWith->sprite->getPosition().x / TILE_SIZE, snakeColidedWith->sprite->getPosition().y / TILE_SIZE);
exit:
    snakeShielded = false;
}
void handleSnakeCollisionWithWall()
{
    if (snakeShielded)
    {
        snakeShielded = false;
        DeleteTile(snakeColidedWith->sprite->getPosition().x / TILE_SIZE, snakeColidedWith->sprite->getPosition().y / TILE_SIZE);
        return;
    }
    handleSnakeDeath();
}

void handleSnakeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && lastInput != Direction::Down)
        lastInput = Direction::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && lastInput != Direction::Up)
        lastInput = Direction::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && lastInput != Direction::Left)
        lastInput = Direction::Right;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && lastInput != Direction::Right)
        lastInput = Direction::Left;
}
void invertSnakeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && lastInput != Direction::Up)
        lastInput = Direction::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && lastInput != Direction::Down)
        lastInput = Direction::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && lastInput != Direction::Right)
        lastInput = Direction::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && lastInput != Direction::Left)
        lastInput = Direction::Right;
}