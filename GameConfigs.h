#pragma once
static int Score = 0;

char const Spritesheet_Path[] = ".\\resources\\snake.png";
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

sf::Vector2f const VOID_INDEX = { GAMEwin_H_MAX + 100, GAMEwin_W_MAX+ 100};