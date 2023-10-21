#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "GameObject.h"
#include <vector>
class PowerUp :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    void setPosition(int x, int y);
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
private:
    int x;
    int y;
    int width;
    int height; 
    int directionY;
    float reloadTime;
    float currentReloadTime;
    SDL_Texture* texture;
};

