#include "Food.h"

void Food::start()
{
	width = 3;
	height = 3;
	texture = loadTexture("gfx/bubble.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Food::update()
{
}

void Food::draw()
{
	blit(texture, x, y);
}

Food::Food(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Food::getPosX()
{
	return this->x;
}

int Food::getPosY()
{
	return this->y;
}

int Food::getWidth()
{
	return this->width;
}

int Food::getHeight()
{
	return this->height;
}
