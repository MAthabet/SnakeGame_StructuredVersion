#include "Collision.h"
#include "Snake.h"
#include "Map.h"
bool checkSelfCollision()
{
    int x = snake[0].getPosition().x;
    int y = snake[0].getPosition().y;
    for (int i = snake.size() - 1; i > 0;i--)
    {
        if (x == snake[i].getPosition().x)
            if (y == snake[i].getPosition().y)
                handleSnakeDeath();
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
    if (checkCollisionWithWindow(j,i))
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
    pawn->sprite->setPosition(GAMEwin_W_MAX+100, GAMEwin_H_MAX+100);
}