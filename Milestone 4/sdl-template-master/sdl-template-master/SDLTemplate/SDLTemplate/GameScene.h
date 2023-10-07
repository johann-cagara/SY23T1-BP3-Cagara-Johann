#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Background.h"
#include "Explosion.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;
	Background* background;
	Explosion* explosion;

	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*>spawnedExplosions;

	void checkSpawn();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;
};

