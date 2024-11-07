#pragma once
enum Axis { Vertical, Horizontal };

void moveAndRotate(sf::Sprite* assest,Axis axis,float linSpeed = 1, float rotSpeed = 30)
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