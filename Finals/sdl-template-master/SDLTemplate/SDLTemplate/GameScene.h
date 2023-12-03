#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Background.h"
#include "Food.h"
#include "text.h"
#include <array>
#include "SoundManager.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	void checkFoodSpawn();
	void doCollisionLogic();
	void foodSpawn();
	void resetGame();
	int highScore(int hello[]);
private:
	Player* head;
	Food* food;
	Background* background;
	float foodTimer;
	float currentFoodTimer;
	int points;
	int pointArray[50];
	int playCount;
	bool gameDone;
	bool resetSequence;
	Mix_Chunk* sound;
	
};

