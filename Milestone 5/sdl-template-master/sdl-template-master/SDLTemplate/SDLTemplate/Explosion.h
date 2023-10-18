#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Explosion :
    public GameObject
{
public:
    Explosion(int x, int y);
    void start();
    void draw();
    void update();
    void explosion();
private:
    SDL_Texture* texture;
    int width;
    int height;
    int x;
    int y;
    int alpha;
};

