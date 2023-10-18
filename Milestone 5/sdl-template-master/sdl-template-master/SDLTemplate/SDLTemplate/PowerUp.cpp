#include "PowerUp.h"

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");

	x = -1;
	y = 1;
	directionY = 1;
	width = 0;
	height = 0;
	reloadTime = 300;
	currentReloadTime = 200;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
{
	y += directionY;
}


void PowerUp::draw()
{
	blit(texture, x, y);

}

void PowerUp::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}
