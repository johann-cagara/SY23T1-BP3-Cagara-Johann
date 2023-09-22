#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

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

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(SCREEN_WIDTH + 100, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}
