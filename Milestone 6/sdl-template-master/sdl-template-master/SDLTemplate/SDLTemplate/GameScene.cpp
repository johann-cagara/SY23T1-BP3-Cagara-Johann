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
	currentpowerUpSpawnTimer = 600;
	powerUpSpawnTime = 600;
	bossSpawnPoints = 5;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	drawText(100, 0, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

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
	checkPowerSpawn();
	playerPowerCollision();
	
	
}

void GameScene::checkSpawn()
{
	if (points < bossSpawnPoints && bossAlive == false)
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
	} else if (points >= bossSpawnPoints)
	{
		if (currentSpawnTimer > 0) {
			currentSpawnTimer--;
		}

		if (currentSpawnTimer <= 0) {
			currentSpawnTimer = spawnTime;


			bossAlive = true;
			enemySpawn();
			currentSpawnTimer = spawnTime;
			bossSpawnPoints += 15;
		}
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
					player->getPositionY(), player->getPositionX(), player->getWidth(), player->getHeight(),
					bullet->getPositionY(), bullet->getPositionX(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					//player->doDeath();
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
						bullet->getPositionY(), bullet->getPositionX(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						if (currentEnemy->getVar() == Variation::BOSS) 
						{
							if (currentEnemy->getBossHp() > 0) 
							{
								currentEnemy->decrementHp();
							}
							else if (currentEnemy->getBossHp() <= 0) 
							{
								bossAlive = false;
								despawnEnemy(currentEnemy);
								points++;
								break;
								
							}
							
						}
						else
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
}


void GameScene::spawn()
{
	Enemy* enemy = new Enemy(Variation::NORMAL);
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(100 + (rand() % 300), 100);
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
		Explosion* explosion = new Explosion(spawnedEnemies[index]->getPositionY(), spawnedEnemies[index]->getPositionX());
		spawnedExplosions.push_back(explosion);
		this->addGameObject(explosion);
		explosion->start();
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;


	}
}
void GameScene::checkPowerSpawn()
{
	if (currentpowerUpSpawnTimer > 0) {
		currentpowerUpSpawnTimer--;
	}

	if (currentpowerUpSpawnTimer <= 0) {
		currentpowerUpSpawnTimer = powerUpSpawnTime;

		powerUpSpawn();

		currentpowerUpSpawnTimer = powerUpSpawnTime;
	}
}

void GameScene::powerUpSpawn()
{
	PowerUp* pUp = new PowerUp();
	this->addGameObject(pUp);

	pUp->setPosition(100 + (rand() % 300), 0);
	spawnedPowerUps.push_back(pUp);

}

void GameScene::playerPowerCollision()
{
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		PowerUp* currentPowerUp = spawnedPowerUps[i];

		int collision = checkCollision(
			player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
			currentPowerUp->getPositionX(), currentPowerUp->getPositionY(), currentPowerUp->getWidth(), currentPowerUp->getHeight()
		);

		if (collision == 1)
		{
			player->setNumberCollision();
			despawnPowerUps(currentPowerUp);
			break;
		}
	}
	
}

void GameScene::despawnPowerUps(PowerUp* pUp)
{
	int index = -1;
	int counter = 0;
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (pUp == spawnedPowerUps[i])
		{
			index = i;
			break;
		}
	}

	if (index != 1)
	{
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete pUp;
	}
}

void GameScene::enemySpawn()
{

	Enemy* boss = new Enemy(Variation::BOSS);
	this->addGameObject(boss);
	boss->setPlayerTarget(player);
	//boss->setHeight(30);
	//boss->setWidth(30);


	boss->setPosition(0, 100);
	spawnedEnemies.push_back(boss);


}



