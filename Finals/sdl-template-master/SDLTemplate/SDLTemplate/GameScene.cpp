#include "GameScene.h"
#include "util.h"
//#include "Player.cpp"

using namespace std;
GameScene::GameScene()
{
	background = new Background();
	this->addGameObject(background);
	head = new Player;
	head->setX(60);
	head->setY(55);
	this->addGameObject(head);
	playCount = 0;
	gameDone = false;
	sound = SoundManager::loadSound("sound/Pop Bubble Sound Effect 2022.mp3");
	// Register and add game objects on constructor

	points = 0;
}

GameScene::~GameScene()
{
	
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();

	currentFoodTimer = 300;
	foodTimer = 300;
}

void GameScene::draw()
{
	Scene::draw();

	drawText(375, 50, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
	
	if (gameDone == true) {
		pointArray[playCount] = points;
		playCount++;
		drawText(375, 310, 255, 255, 255, TEXT_CENTER, "GAME OVER");
		drawText(375, 360, 255, 255, 255, TEXT_CENTER, "HIGHEST SCORE: %03d", highScore(pointArray));
		drawText(380, 410, 255, 255, 255, TEXT_CENTER, "BACKSPACE - RETRY");
		drawText(375, 460, 255, 255, 255, TEXT_CENTER, "ESC - EXIT");
	}
}

void GameScene::update()
{
	Scene::update();

	if (resetSequence == true)
	{
		resetGame();

	}

	if (!gameDone)
	{
		checkFoodSpawn();
		doCollisionLogic();
	}
	if (!head->playerAlive)
	{
		gameDone = true;
		if (app.keyboard[SDL_SCANCODE_BACKSPACE])
		{
			resetSequence = true;
		}
		else if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			exit(0);
		}
	}
}

void GameScene::checkFoodSpawn()//spawns the food in intervals
{
	if (currentFoodTimer > 0) {
		currentFoodTimer--;
	}
	if (currentFoodTimer <= 0) {
		currentFoodTimer = foodTimer;

		foodSpawn();

		currentFoodTimer = foodTimer;
	}
}

void GameScene::doCollisionLogic()//function to check collision between player and the food
{
	for (int i = 0; i < objects.size(); i++)
	{
		Food* food = dynamic_cast<Food*>(objects[i]);

		if (food != NULL)
		{
			int collision = checkCollision(
				head->bodyExt[0].x, head->bodyExt[0].y, head->getWidth(), head->getHeight(),
				food->getPosX(), food->getPosY(), food->getWidth(), food->getHeight()
			);
			
			if (collision == 1)
			{
				SoundManager::playSound(sound);
				head->addBody();

				points++;
				delete food;

				break;
			}
		}

	}
}

void GameScene::foodSpawn()//function to spawn the food in random coordinates across the board
{
	int i = rand() % 9 + 1;
	int k = rand() % 9 + 1;
	Food* food = new Food(70 + (i * 62), 70 + (k * 62));
	//Food* food = new Food(1, 1);
	this->addGameObject(food);
}

void GameScene::resetGame()//function to reset game
{
	head->resetSnake();
	gameDone = false;
	points = 0;

	resetSequence = false;
}

int GameScene::highScore(int hello[])//function to store high scores per game inside an array to be sorted out to get the highest score
{
	for (int i = 0; i < playCount; i++)
	{
		int max = i;

		for (int k = i + 1; k < playCount; k++)
		{
			if (hello[k] > hello[max])
			{
				max = k;
			}
		}

		int temp = hello[i];
		hello[i] = hello[max];
		hello[max] = temp;
	}
	return hello[0];
}

