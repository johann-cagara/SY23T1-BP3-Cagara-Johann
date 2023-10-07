#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
class Player :
    public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float reloadTimeFront;
	float reloadTimeSides;
	float currentReloadTime;
	std::vector<Bullet*> bullets;
	bool isAlive;
};

