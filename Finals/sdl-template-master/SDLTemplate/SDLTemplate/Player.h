#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>

struct BodyPart
{
    int x;
    int y;
    int textureType;
};

class Player :
    public GameObject
{
public:
    
    void start();
    void update();
    void draw();
    int getWidth();
    int getHeight();
    void setX(int i);
    void setY(int i);
    int getX();
    int getY();
    void addBody();
    void moveBody();
    std::vector<BodyPart> bodyExt;
    bool playerAlive;
    void resetSnake();
private:
    int x;
    int y;
    int width;
    int height;
    int changeDirection;
    int tileIncrement;
    float currentMoveTimer;
    float moveTime;
    
    SDL_Texture* texture;
    SDL_Texture* texture1;
    Mix_Chunk* sound;
    
};

