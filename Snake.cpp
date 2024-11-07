#include "Snake.h"

void drawSnake(sf::RenderWindow* win)
{
    for (auto& spirit : snake)
    {
        win->draw(spirit);
    }
}

void initSnake(int snakeLength, sf::Vector2f start)
{
    head.setPosition(start);
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
        invertedInput = false;
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
            invertedInput = false;
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
void handleSnakeDeath()
{
    snakeAlive = false;
}