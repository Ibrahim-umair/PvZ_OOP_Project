#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "plants.h"
#include <cstdlib>
#include <time.h>
using namespace std;
using namespace sf;


////////zombie class///////
class Zombie
{
protected:
	int health;
	float speed;
	int damage;
	int row;
	bool isAttacking;
	Vector2f position;
	Sprite zomSprite;
	Texture zomTexture;
	Clock zomClock;
	Clock animationClock;
	Sprite attackSprite;
	Texture attackTexture;
	Clock attackClock;
	bool exist;

public:

	bool isAlive()
	{
		return exist;
	}
	void setFinish()
	{
		exist = !exist;
	}

	virtual void draw(RenderWindow& window, int x, int y) {}
	virtual void move(RenderWindow& window, int DiversionY, int Cell_Size_Y) {}
	virtual void checkPlantCollision(Plant** plant, int numPlants) {}
	Vector2f getPosition()
	{
		return position;
	}

	int getRow()
	{
		return row;
	}

};

class NormalZombie : public Zombie
{
	IntRect zomFrames[7];
	int currentFrame;
	IntRect attackFrames[7];
	int currentAttackFrame;

public:

	NormalZombie()
	{
		
		zomTexture.loadFromFile("../PZ_Project/PVZ/Zombies/movingzomb3.png");
		zomSprite.setTexture(zomTexture);
		zomSprite.setScale(2.0f, 2.0f);

		attackTexture.loadFromFile("../PZ_Project/PVZ/Zombies/simplezombie.png");
		attackSprite.setTexture(attackTexture);
		attackSprite.setScale(2.5f, 2.5f);
		
		int frameWidth = 47, frameHeigth = 48;
		for (int i = 0; i < 7; ++i)
		{
			zomFrames[i] = IntRect(i * frameWidth + 2 * i, 5, frameWidth, frameHeigth);
		}
		row = rand() % 5;

		position.x = 980;
		int DiversionY = 144;
		int Cell_Size_Y = 98;

		position.y = DiversionY + row * Cell_Size_Y;
		speed = 5;
		damage = 1;
		exist = 1;
		health = 100;
		isAttacking = false;

		currentFrame = 0;

		////////////////////
		//attack animation//
		////////////////////

		int attackFrameWidth = 35, attackFrameHeigth = 41;
		for (int i = 0; i < 7; ++i)
		{
			attackFrames[i] = IntRect(i * attackFrameWidth + 2*i, 0, attackFrameWidth, attackFrameHeigth);
		}
		currentAttackFrame = 0;

	}
	virtual void move()
	{

		if (zomClock.getElapsedTime().asSeconds() > 0.5)
		{
			position.x -= speed;
			zomClock.restart();
		}
	}

	virtual void draw(RenderWindow& window, int DiversionY, int Cell_Size_Y)
	{
		if (isAttacking)
		{
			drawAtt(window);
			return;
		}

		move();
		zomSprite.setPosition(position.x, position.y);
		zomSprite.setTextureRect(zomFrames[currentFrame]);
		window.draw(zomSprite);


		if (animationClock.getElapsedTime().asSeconds() > 0.5)
		{
			currentFrame++;
			if (currentFrame >= 7)
			{
				currentFrame = 0;
			}
			animationClock.restart();
		}

	}

	void drawAtt(RenderWindow& window)      ///////drawing animations
	{
		attackSprite.setPosition(position.x, position.y - 12);
		attackSprite.setTextureRect(attackFrames[currentAttackFrame]);
		window.draw(attackSprite);

		if (attackClock.getElapsedTime().asSeconds() > 0.5)
		{
			currentAttackFrame++;
			if (currentAttackFrame >= 7)
			{
				currentAttackFrame = 0;
			}
			attackClock.restart();
		}
	}

	virtual void checkPlantCollision(Plant** plant, int numPlants)  ////////collision logic
	{
		for (int i = 0; i < numPlants; i++)
		{
			if (plant[i]->getRow() == row)
			{
				if (position.x - plant[i]->getPosition().x < 50 && plant[i]->isExist)
				{
					//cout<<plant[i]->getHealth()<<endl;
					plant[i]->decreaseHealth(damage);
					isAttacking = true;
					break;
				}
				else
				{
					isAttacking = false;
				}
			}
		}

	}

};

class FootballZombie : public Zombie
{
protected:
	IntRect zomFrames[8];
	int currentFrame;
	IntRect attackFrames[6];
	int currentAttackFrame;


	public:

	FootballZombie()
	{
	zomTexture.loadFromFile("../PZ_Project/PVZ/Zombies/footballzomb.png");
	zomSprite.setTexture(zomTexture);
	zomSprite.setScale(2.5f, 2.5f);

	int frameWidth = 39, frameHeigth = 100;
	for (int i = 0; i < 8; ++i)
	{
		zomFrames[i] = IntRect(i * frameWidth ,0, frameWidth, frameHeigth);
	}
	row = rand() % 5;

	position.x = 980;
	int DiversionY = 134;
	int Cell_Size_Y = 98;

	position.y = DiversionY + row * Cell_Size_Y;
	speed = 5;
	exist = 1;
	isAttacking = false;

	currentFrame = 0;

	health = 150;
	////////////////////
	//attack animation//
	////////////////////

	attackTexture.loadFromFile("../PZ_Project/PVZ/Zombies/footzombeat.png");
	attackSprite.setTexture(attackTexture);
	attackSprite.setScale(2.5f, 2.5f);

	int attackFrameWidth = 38, attackFrameHeigth = 36;
	
	for (int i = 0; i < 6; ++i)
	{
		attackFrames[i] = IntRect(i * attackFrameWidth, 0, attackFrameWidth, attackFrameHeigth);
	}
	currentAttackFrame = 0;
	damage = 1;

	}

	virtual void move()
	{
		if (zomClock.getElapsedTime().asSeconds() > 0.1)
		{
			position.x -= speed;
			zomClock.restart();
		}

	}



	virtual void draw(RenderWindow& window, int DiversionY, int Cell_Size_Y)
	{
		if (isAttacking)
		{
			drawAtt(window);
			return;
		}


		move();
		zomSprite.setPosition(position.x, position.y);
		zomSprite.setTextureRect(zomFrames[currentFrame]);
		window.draw(zomSprite);

		if (animationClock.getElapsedTime().asSeconds() > 0.5)
		{
			currentFrame++;
			if (currentFrame >= 8)
			{
				currentFrame = 0;
			}
			animationClock.restart();
		}
	}

	void drawAtt(RenderWindow& window)
	{
		attackSprite.setPosition(position.x, position.y+12 );
		attackSprite.setTextureRect(attackFrames[currentAttackFrame]);
		window.draw(attackSprite);

		if (attackClock.getElapsedTime().asSeconds() > 1)
		{
			currentAttackFrame++;
			if (currentAttackFrame >= 6)
			{
				currentAttackFrame = 0;
			}
			attackClock.restart();
		}
	}

	virtual void checkPlantCollision(Plant** plant, int numPlants)
	{
		for (int i = 0; i < numPlants; i++)
		{
			if (plant[i]->getRow() == row)
			{

				if (position.x + 30 > (plant[i]->getPosition().x ) && position.x - plant[i]->getPosition().x < 50 && plant[i]->isExist)
				{
					plant[i]->decreaseHealth(damage);
					isAttacking = true;
					break;
				}
				else
				{
					isAttacking = false;
				}
			}
		}
	
	}

};

class BalloonZombie : public Zombie
{
	IntRect zomFrames[10];
	int currentFrame;
	int yMax;
	int ySpeed;
	public:

		BalloonZombie()
		{
			zomTexture.loadFromFile("../PZ_Project/PVZ/Zombies/balloonzomb.png");
			zomSprite.setTexture(zomTexture);
			zomSprite.setScale(2.0f, 2.0f);

			int frameWidth = 34, frameHeigth = 57;
			for (int i = 0; i < 10; ++i)
			{
				
				zomFrames[i] = IntRect(i * frameWidth, 0, frameWidth, frameHeigth);
			}
			row = rand() % 5;

			position.x = 980;
			int DiversionY = 144;
			int Cell_Size_Y = 98;
			ySpeed = 2;
			position.y = DiversionY + row * Cell_Size_Y;
			yMax = position.y - 50;
			speed = 5;
			exist = 1;
			health = 80;
			isAttacking = false;

			currentFrame = 0;
		
		}

		virtual void move()
		{
			if (zomClock.getElapsedTime().asSeconds() > 0.2)
			{
				position.x -= speed;
				position.y -= ySpeed;
				zomClock.restart();
			}
		}

		virtual void draw(RenderWindow& window, int DiversionY, int Cell_Size_Y)
		{
			if(position.y <= yMax)
			{
				ySpeed = 0;
			}
			if (position.x <= (260 + 80 * 2) )
			{ySpeed = -2;
			}

			move();
			zomSprite.setPosition(position.x, position.y);
			zomSprite.setTextureRect(IntRect(0,0,33,57));
			window.draw(zomSprite);

			if (animationClock.getElapsedTime().asSeconds() > 1)
			{
				currentFrame++;
				if (currentFrame >= 10)
				{
					currentFrame = 0;
				}
				animationClock.restart();
			}
		}
		};

class DancingZombie : public Zombie
{
	IntRect zomFrames[4];
	int currentFrame;

	public:

	DancingZombie()
	{
		zomTexture.loadFromFile("../PZ_Project/PVZ/Zombies/dancingzomb.png");
		zomSprite.setTexture(zomTexture);
		zomSprite.setScale(1.5f, 1.5f);

		int frameWidth = 50, frameHeigth = 63;
		for (int i = 0; i < 4; ++i)
		{
			zomFrames[i] = IntRect(i * frameWidth, 0, frameWidth, frameHeigth);
		}
		row = rand() % 5;

		position.x = 980;
		int DiversionY = 144;
		int Cell_Size_Y = 98;

		position.y = DiversionY + row * Cell_Size_Y;
		speed = 5;
		exist = 1;
		isAttacking = false;
		health = 120;
		currentFrame = 0;
	}

	virtual void move()
	{
		if (zomClock.getElapsedTime().asSeconds() > 0.3)
		{
			position.x -= speed;
			zomClock.restart();
		}
	}

	virtual void draw(RenderWindow& window, int DiversionY, int Cell_Size_Y)
	{
		move();
		zomSprite.setPosition(position.x, position.y);
		zomSprite.setTextureRect(zomFrames[currentFrame]);
		window.draw(zomSprite);

		if (animationClock.getElapsedTime().asSeconds() > 0.3)
		{
			currentFrame++;
			if (currentFrame >= 4)
			{
				currentFrame = 0;
			}
			animationClock.restart();
		}
	}
};

class ZombieFactory
{
public:
	Zombie** zombies;
	int numofZomb=5;
	

	ZombieFactory()
	{
		numofZomb= 5;
		srand(time(0));
		zombies = new Zombie * [5];
		zombies[0] = new NormalZombie(); 
		zombies[1] = new FootballZombie();
		zombies[2] = new DancingZombie();
		zombies[3] = new BalloonZombie();
		zombies[4] = new FootballZombie();
	}
	virtual void moveZombies(RenderWindow& window, int DiversionY, int Cell_Size_Y, int& lives)
	{
		for (int i = 0; i < 5; i++)
		{
			if (zombies[i]->isAlive())
			{
				zombies[i]->draw(window, DiversionY, Cell_Size_Y);
				if(zombies[i]->getPosition().x < 250)
				{

					zombies[i]->setFinish();
					lives--;
				}
			}
		}
	}
	void checkPlantCollision(Plant** plants, int numPlants)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0;j < numPlants;j++)
			{
				zombies[i]->checkPlantCollision(plants, numPlants);
			}
		}
	}

	~ZombieFactory()
	{
		for (int i = 0; i < 5; i++)
		{
			delete zombies[i];
		}
		delete[] zombies;
	}

};
