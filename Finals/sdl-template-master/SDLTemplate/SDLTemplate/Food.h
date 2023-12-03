#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
class Food :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    Food(int x, int y);
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
private:
    int x;
    int y;
    int height;
    int width;
    SDL_Texture* texture;
};

