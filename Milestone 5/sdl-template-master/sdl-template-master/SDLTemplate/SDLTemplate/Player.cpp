#include "Player.h"
#include "Scene.h"
using namespace std;

static bool powerUpCollided = false;
static int numberCollision;
Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	// load texture
	texture = loadTexture("gfx/player.png");

	
	x = SCREEN_WIDTH/2;
	y = SCREEN_HEIGHT - 400;
	width = 0;
	height = 0;
	speed = 2;
	reloadTimeFront = 8;
	reloadTimeSides = 15;
	currentReloadTime = 0;
	isAlive = true;
	
	numberCollision = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getPositionY() < 0) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W]) {
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S]) {
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A]) {
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D]) {
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT]) {
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE]) {
		speed = 2;
	}

	if (currentReloadTime > 0) {
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		addBullet();
		
		currentReloadTime = reloadTimeFront;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		addBulletSides();


		currentReloadTime = reloadTimeSides;
	}

}

void Player::draw()
{
	if (!isAlive) return;

	blit(texture, x, y);
	
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::addBullet()
{

	Bullet* bullet = new Bullet(x - 27 + width, y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
	bullets.push_back(bullet);
	getScene()->addGameObject(bullet);
	bullet->start();

	if(numberCollision != 0) {
		for (int i = 1; i < numberCollision+1; i++)
		{
			Bullet* bullet = new Bullet(x - 27 - i*10 + width, y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
			Bullet* bullet1 = new Bullet(x - 27 + i*10 + width, y - 25 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
			bullet->start();

			bullets.push_back(bullet1);
			getScene()->addGameObject(bullet1);
			bullet1->start();

		}
	}
	
	
}

void Player::addBulletSides()
{
	Bullet* leftBullet = new Bullet(x - 2, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
	Bullet* rightBullet = new Bullet(x - 2 + width, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
	bullets.push_back(leftBullet);
	bullets.push_back(rightBullet);
	getScene()->addGameObject(leftBullet);
	getScene()->addGameObject(rightBullet);
	leftBullet->start();
	rightBullet->start();

	if (numberCollision != 0) {
		for (int i = 1; i < numberCollision + 1; i++)
		{
			Bullet* bullet = new Bullet(x - 2 - i * 10, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
			Bullet* bullet1 = new Bullet(x - 2 + i * 10, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
			Bullet* bullet2 = new Bullet(x - 2 + width - i * 10, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
			Bullet* bullet3 = new Bullet(x - 2 + width + i * 10, y + 10, 0, -1, 10, Side::PLAYER_SIDE);
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

		}
	}
}

void Player::setNumberCollision()
{
	numberCollision+=1;
}

