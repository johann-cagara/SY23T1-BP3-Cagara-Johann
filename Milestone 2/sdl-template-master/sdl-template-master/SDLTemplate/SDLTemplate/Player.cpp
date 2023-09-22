#include "Player.h"
#include "Scene.h"

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

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTimeFront = 8;
	reloadTimeSides = 15;
	currentReloadTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		currentReloadTime = reloadTimeFront;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		Bullet* leftBullet = new Bullet(x + 2, y - 1, 1, 0, 10);
		Bullet* rightBullet = new Bullet(x + 2, y - 2 + height, 1, 0, 10);
		bullets.push_back(leftBullet);
		bullets.push_back(rightBullet);
		getScene()->addGameObject(leftBullet);
		getScene()->addGameObject(rightBullet);
		leftBullet->start();
		rightBullet->start();

		currentReloadTime = reloadTimeSides;
	}

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getPositionX() > SCREEN_WIDTH) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
