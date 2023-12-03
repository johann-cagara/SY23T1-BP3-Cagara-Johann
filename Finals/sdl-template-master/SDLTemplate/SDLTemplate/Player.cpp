#include "Player.h"

using namespace std;

void Player::start()
{
	width = 0;
	height = 0;
	tileIncrement = 62;
	currentMoveTimer = 0;
	moveTime = 10;
	sound = SoundManager::loadSound("sound/La vaguelette.mp3");
	playerAlive = true;
	
	SoundManager::playSound(sound);

	texture = loadTexture("gfx/head.png");
	addBody();

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Player::update()
{
	if (playerAlive == true)		//if player dies, player won't be able to move
	{
		if (currentMoveTimer > 0)
		{
			currentMoveTimer--;
		}

		//changeDirection is needed to have constant movement 

		if (app.keyboard[SDL_SCANCODE_W])
		{
			if (changeDirection == 2)
			{
				changeDirection = 2;
			}
			else
			{
				changeDirection = 1;
			}
		}
		else if (app.keyboard[SDL_SCANCODE_S])
		{
			if (changeDirection == 1)
			{
				changeDirection = 1;
			}
			else
			{
				changeDirection = 2;
			}
		}
		else if (app.keyboard[SDL_SCANCODE_A])
		{
			if (changeDirection == 4)
			{
				changeDirection = 4;
			}
			else
			{
				changeDirection = 3;
			}

		}
		else if (app.keyboard[SDL_SCANCODE_D])
		{
			if (changeDirection == 3)
			{
				changeDirection = 3;
			}
			else
			{
				changeDirection = 4;
			}

		}

		if (changeDirection != 0 && currentMoveTimer == 0)
		{
			//once the player hits the border, the player dies
			if (changeDirection == 1)
			{
				y -= tileIncrement;
				if (y < 55) {
					y = 55;
					playerAlive = false;
				}
			}
			else if (changeDirection == 2)
			{
				y += tileIncrement;
				if (y > 613) {
					y = 613;
					playerAlive = false;
				}
			}
			else if (changeDirection == 3)
			{
				x -= tileIncrement;
				if (x < 60) {
					x = 60;
					playerAlive = false;
				}
			}
			else
			{
				x += tileIncrement;
				if (x > 618) {
					x = 618;
					playerAlive = false;
				}
			}

			moveBody();
			currentMoveTimer = moveTime;
		}
	}

}

void Player::draw()
{
	//draws the body/ies according to their assigned textures
	for (int i = 0; i < bodyExt.size(); i++)
	{
		if (bodyExt[i].textureType == 0)
		{
			texture = loadTexture("gfx/head.png");
		}
		else if (bodyExt[i].textureType == 1)
		{
			texture = loadTexture("gfx/pet1.png");
		}
		else if (bodyExt[i].textureType == 2)
		{
			texture = loadTexture("gfx/pet2.png");
		}
		else
		{
			texture = loadTexture("gfx/pet3.png");
		}

		if (bodyExt.size() == 1) {
			blit(texture, x, y);
		}
		else {
			blit(texture, bodyExt[i].x, bodyExt[i].y);
		}
		
	}
	
}

int Player::getWidth()
{
	return this->width;
}

int Player::getHeight()
{
	return this->height;
}

void Player::setX(int i)
{
	this->x = i;
}

void Player::setY(int i)
{
	this->y = i;
}

int Player::getX()
{
	return this->x;
}

int Player::getY()
{
	return this->y;
}

void Player::addBody()			//function to add body
{
	BodyPart* newBody = new BodyPart{ x, y, 0 };
	if (bodyExt.size() == 0)
	{

		if (changeDirection == 1)
		{
			newBody->x = x;
			newBody->y = y + tileIncrement;
			newBody->textureType = rand() % 3 + 1;
			if (y < 55) {
				y = 55;
				playerAlive = false;
			}
		}
		else if (changeDirection == 2)
		{
			newBody->x = x;
			newBody->y = y - tileIncrement;
			newBody->textureType = rand() % 3 + 1;

			if (y > 613) {
				y = 613;
				playerAlive = false;
			}
		}
		else if (changeDirection == 3)
		{
			newBody->x = x + tileIncrement;
			newBody->y = y;
			newBody->textureType = rand() % 3 + 1;

			if (x < 60) {
				x = 60;
				playerAlive = false;
			}
		}
		else if (changeDirection == 4)
		{
			newBody->x = x - tileIncrement;
			newBody->y = y;
			newBody->textureType = rand() % 3 + 1;
			if (x > 618) {
				x = 618;
				playerAlive = false;
			}
		}
		
	}
	else
	{
		if (changeDirection == 1)
		{
			newBody->x = bodyExt[bodyExt.size() - 1].x;
			newBody->y = bodyExt[bodyExt.size() - 1].y + tileIncrement;
			newBody->textureType = rand() % 3 + 1;
		}
		else if (changeDirection == 2)
		{
			newBody->x = bodyExt[bodyExt.size() - 1].x;
			newBody->y = bodyExt[bodyExt.size() - 1].y - tileIncrement;
			newBody->textureType = rand() % 3 + 1;
		}
		else if (changeDirection == 3)
		{
			newBody->x = bodyExt[bodyExt.size() - 1].x + tileIncrement;
			newBody->y = bodyExt[bodyExt.size() - 1].y;
			newBody->textureType = rand() % 3 + 1;
		}
		else if (changeDirection == 4)
		{
			newBody->x = bodyExt[bodyExt.size() - 1].x - tileIncrement;
			newBody->y = bodyExt[bodyExt.size() - 1].y;
			newBody->textureType = rand() % 3 + 1;
		}
		
	}
	bodyExt.push_back(*newBody);

	

}

void Player::moveBody()
{
	//the x and y of each body will be a copy of the previous body before them (first body follows the head)
	int prevPosX = x;
	int prevPosY = y;

	for (int i = 0; i < bodyExt.size(); i++)
	{
		int tempX = bodyExt[i].x;
		int tempY = bodyExt[i].y;

		bodyExt[i].x = prevPosX;
		bodyExt[i].y = prevPosY;

		prevPosX = tempX;
		prevPosY = tempY;

		
	}

	//collision check: if player collides with itself, player dies

	for (int k = 1; k < bodyExt.size(); k++)
	{
		if (bodyExt[0].x == bodyExt[k].x && bodyExt[0].y == bodyExt[k].y)
		{
			playerAlive = false;
		}
	}

}

void Player::resetSnake()	//function to reset the snake
{
	x = 60;
	y = 55;
	
	for (int i = bodyExt.size() - 1; i > 0; i--) 
	{
		bodyExt.erase(bodyExt.begin() + i);
	}

	playerAlive = true;
	changeDirection = 0;
}
