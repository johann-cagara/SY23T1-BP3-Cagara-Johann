#include "Explosion.h"

using namespace std;

Explosion::Explosion(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Explosion::start()
{
	alpha = rand() % 60 * 2.5;
	width = 0;
	height = 0;
}

void Explosion::draw()
{

	texture = loadTexture("gfx/explosion.png");
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);

	SDL_SetTextureAlphaMod(texture, alpha);
	blit(texture, x, y);
}

void Explosion::update()
{
	explosion();
}

void Explosion::explosion()
{
	if (--this->alpha <= 0) {
		delete this;
	}
}

