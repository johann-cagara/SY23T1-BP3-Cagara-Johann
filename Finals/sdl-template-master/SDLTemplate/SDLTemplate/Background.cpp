#include "Background.h"

Background::Background()
{
}

void Background::start()
{
	height = 512;
	texture = loadTexture("gfx/background.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Background::draw()
{
	blitScale(texture, 0, 0, &width, &height, 1);
}
