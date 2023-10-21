#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Explosion.h"
#include <vector>
#include "util.h"
#include "Player.h"

enum class Variation
{
	NORMAL,
	BOSS
};

class Enemy : public GameObject
{
public:
	Enemy(Variation var);
	~Enemy();
	void start();
	void update();
	void draw();
	void setPlayerTarget(Player* player);
	void setPosition(int x, int y);
	void setWidth(int width);
	void setHeight(int height);
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	int getBossHp();
	void decrementHp();
	Variation getVar();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* playerTarget;
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	float speed;
	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
	std::vector<Bullet*> bullets;
	Variation var;
	int bossHp;
};

