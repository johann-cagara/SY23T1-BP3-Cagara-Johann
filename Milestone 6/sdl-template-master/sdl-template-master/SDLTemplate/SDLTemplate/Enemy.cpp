#include "Enemy.h"
#include "Scene.h"
#include "Explosion.h"


Enemy::Enemy(Variation var)
{
	this->var = var;
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	// load texture
	if (this->var == Variation::NORMAL)
	{
		texture = loadTexture("gfx/enemy.png");
	}else{
		texture = loadTexture("gfx/boss.png");
	}
	

	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;

	if (var == Variation::BOSS) {
		speed = 1;
		reloadTime = 20;
		width = 20;
		height = 20;
	}
	else {
		speed = 3;
		reloadTime = 60;
	}
	
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 180;
	currentDirectionChangeTime = 0;
	if (this->var == Variation::BOSS) 
	{
		this->bossHp = 100;
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0) {
		currentDirectionChangeTime--;
	}
	if (currentDirectionChangeTime == 0) {
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0) {
		currentReloadTime--;
	}

	if (currentReloadTime == 0) {
		float dx = -1;
		float dy = 0;
		SoundManager::playSound(sound);

		if (var == Variation::BOSS) 
		{
			float dx = (rand() % 10 + 1) * -1;
			float dy = rand() % 10;

			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

			Bullet* bullet = new Bullet(y - 2 + height / 2, x + width, dx, dy, 50, Side::ENEMY_SIDE);
			Bullet* bullet1 = new Bullet(y - 10 + height / 2, x - 30 + width, dx, dy, 10, Side::ENEMY_SIDE);
			Bullet* bullet2 = new Bullet(y + 40 + height / 2, x + 10 + width, dx, dy, 25, Side::ENEMY_SIDE);
			Bullet* bullet3 = new Bullet(y + 60 + height / 2, x + 5+ width, dx, dy, 17, Side::ENEMY_SIDE);
			Bullet* bullet4 = new Bullet(y - 80 + height / 2, x  + 15 + width, dx, dy, 5, Side::ENEMY_SIDE);
			Bullet* bullet5 = new Bullet(y - 100 + height / 2, x + 15 + width, dx, dy, 5, Side::ENEMY_SIDE);
			Bullet* bullet6 = new Bullet(y - 120 + height / 2, x + 15 + width, dx, dy, 5, Side::ENEMY_SIDE);

			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
			bullet->start();
			bullets.push_back(bullet1);
			getScene()->addGameObject(bullet1);
			bullet1->start();
			bullets.push_back(bullet2);
			getScene()->addGameObject(bullet2);
			bullet2->start();
			bullets.push_back(bullet3);
			getScene()->addGameObject(bullet3);
			bullet3->start();
			bullets.push_back(bullet4);
			getScene()->addGameObject(bullet4);
			bullet4->start();
			bullets.push_back(bullet5);
			getScene()->addGameObject(bullet5);
			bullet5->start();
			bullets.push_back(bullet6);
			getScene()->addGameObject(bullet6);
			bullet6->start();

			
		}
		else {
			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

			Bullet* bullet = new Bullet(y - 2 + height / 2, x + width, dx, dy, 10, Side::ENEMY_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
			bullet->start();
		}

		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getPositionX() < 0) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, y, x);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Enemy::setWidth(int width)
{
	this->width = width;
}

void Enemy::setHeight(int height)
{
	this->height = height;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}

int Enemy::getBossHp()
{
	return bossHp;
}

void Enemy::decrementHp()
{
	this->bossHp--;
}

Variation Enemy::getVar()
{
	return var;
}


int Enemy::getPositionX()
{
	return x;
}

