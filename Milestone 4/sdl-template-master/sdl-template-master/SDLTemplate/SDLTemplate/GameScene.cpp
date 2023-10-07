#include "GameScene.h"

using namespace std;

GameScene::GameScene()
{
	background = new Background();
	this->addGameObject(background);

	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false) 
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	Scene::update();

	checkSpawn();
	doCollisionLogic();
}

void GameScene::checkSpawn()
{
	if (currentSpawnTimer > 0) {
		currentSpawnTimer--;
	}

	if (currentSpawnTimer <= 0) {
		currentSpawnTimer = spawnTime;

		for (int i = 0; i < 3; i++) {
			spawn();
		}

		currentSpawnTimer = spawnTime;
	}

	for (int i = 0; i < spawnedEnemies.size(); i++) {
		if (spawnedEnemies[i]->getPositionX() < -10 || spawnedEnemies[i]->getPositionY() > SCREEN_HEIGHT || spawnedEnemies[i]->getPositionY() < -10) {
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemyToErase;

			break;
		}
	}
}

void GameScene::doCollisionLogic()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						despawnEnemy(currentEnemy);
						points++;
						break;
					}
				}
			}
		}
	}
}


void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(SCREEN_WIDTH + 100, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	int counter = 0;
	for (int i = 0; i < spawnedEnemies.size(); i++) 
	{
		if (enemy == spawnedEnemies[i]) 
		{
			index = i;
			break;
		}
	}
	
	if (index != 1) 
	{
		Explosion* explosion = new Explosion(spawnedEnemies[index]->getPositionX(), spawnedEnemies[index]->getPositionY());
		spawnedExplosions.push_back(explosion);
		this->addGameObject(explosion);
		explosion->start();
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;


	}
}


