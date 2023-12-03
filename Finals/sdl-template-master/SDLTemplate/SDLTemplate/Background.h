#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
class Background :
    public GameObject
{
public:
	Background();
	void start();
	void draw();
private:
	SDL_Texture* texture;
	int width;
	int height;
};

