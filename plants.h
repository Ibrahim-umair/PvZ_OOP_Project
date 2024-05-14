#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "sun.h"
using namespace std;
using namespace sf;

class Plant
{
protected:
	Texture plantTexture;
	Sprite plantSprite;
	int health;
	int cost;
	Vector2f position;
	Clock animate;
	Clock bulletTime;
	int row;


public:
	bool isExist = true;
	virtual void draw(RenderWindow& window) = 0;
	virtual void shoot(RenderWindow& window) = 0;
	//virtual void checkPlantCollision(Zombie **, int numofZomb) {}

	Vector2f getPosition()
	{
		return position;
	}
	int getRow()
	{
		return row;
	}
	int getHealth()
	{
		return health;
	}
	void decreaseHealth(int damage)
	{
		health -= damage;
	}
	void setExist(bool exist)
	{
		isExist = false;
	}
};




class Projectile
{
private:
	Texture projectileTexture;
	Sprite projectileSprite;
	float speed;
	int damage;
	Vector2f position;
	int row;
public:
	Projectile(int damage, float speed, const string& textureFile, Vector2f stPos)
	{
		projectileTexture.loadFromFile(textureFile);
		projectileSprite.setTexture(projectileTexture);
		projectileSprite.setScale(2.0f, 2.0f);
		this->speed = speed;
		this->damage = damage;
		projectileSprite.setPosition(stPos);
		row = (stPos.y - 174) / 98;

	}

	void draw(RenderWindow& window, int x, int y)
	{
		projectileSprite.setPosition(x , y);
		window.draw(projectileSprite);
	}



	void move(RenderWindow& window)       //////////moving based upon the speed
	{

		position.x += speed;
		projectileSprite.setPosition(position);
		draw(window, position.x, position.y);
	}

	void setPositon(Vector2f pos)
	{
		position = pos;
	}

	Vector2f getPosition()
	{
		return projectileSprite.getPosition();
	}

	//bool checkcollision(Zombie** zombie,int numofZomb)
	//{
	//	for (int i = 0; i < numofZomb; i++)
	//	{
	//		if (zombie[i]->getRow() == row)
	//		{
	//			if (position.x + 30 > (zombie[i]->getPosition().x) && position.x - zombie[i]->getPosition().x < 50 && zombie[i]->isAlive())
	//			{
	//				//zombie[i]->decreaseHealth(damage);
	//				position.x = 1000;
	//				return false;
	//				break;
	//			}
	//		}
	//		
	//	}

	//}
};

class Peashooter : public Plant
{
private:

	IntRect animationFrames[8];
	int currentFrame;
	Projectile bullet;
	bool exist = true;
	

public:
	Peashooter(int x, int y) : bullet(10, 4, "../PZ_Project/PVZ/Plants/pea.png", plantSprite.getPosition())
	{
		position.x = x;
		position.y = y;
		row = (y - 174 )/ 98;
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/Peashooter2.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);

		int frameWidth = 26;
		for (int i = 0; i < 8; ++i)
		{
			animationFrames[i] = IntRect(i * frameWidth + i, 0, frameWidth, 32);
		}


		currentFrame = 0;
		health = 1000;
		isExist = true;
	}
	bool getExist() 
	{
		return isExist;
	
	}


	virtual void draw(RenderWindow& window)  ////drawiing + animation
	{
		plantSprite.setTextureRect(animationFrames[currentFrame]);

		plantSprite.setPosition(position.x, position.y);
		window.draw(plantSprite);

		if (animate.getElapsedTime().asSeconds() > 0.1)
		{
			currentFrame = (currentFrame + 1) % 8;
			animate.restart();
		}

	}


	void shoot(RenderWindow& window)      ////shooting the bullet
	{
		Vector2f temp = position;
		temp.x += 45;
		temp.y += 7;

		if (bullet.getPosition().x == 0)
			bullet.setPositon(temp);
		else if (bullet.getPosition().x >= 960)
		{
			exist = false;
			bullet.setPositon(temp);
			if (bulletTime.getElapsedTime().asSeconds() > 2)
			{
				exist = true;
				bulletTime.restart();
			}
		}
		if (exist)
			bullet.move(window);

	}
	/*virtual void checkPlantCollision(Zombie** zombie, int numofZomb)
	{
		exist = bullet.checkcollision(zombie, numofZomb);
	}*/


	Vector2f getPosition()
	{
		return plantSprite.getPosition();
	}

};

class Snowpea : public Plant    
{
private:
	IntRect animationFrames[8];
	int currentFrame;
	Projectile bullet;
	bool exist = true;

public:
	Snowpea(int x, int y) : bullet(5, 4, "../PZ_Project/PVZ/Plants/snowball.png", plantSprite.getPosition())
	{

		position.x = x;
		position.y = y;
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/snowpea2.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);

		int frameWidth = 30, frameHeight = 32;
		for (int i = 0; i < 8; ++i)
		{
			animationFrames[i] = IntRect(i * frameWidth, 0, frameWidth, frameHeight);
		}
		row = (y - 174) / 98;

		currentFrame = 0;
		health = 1000;

	}

	virtual void draw(RenderWindow& window)
	{
		plantSprite.setTextureRect(animationFrames[currentFrame]);

		plantSprite.setPosition(position.x, position.y);
		window.draw(plantSprite);

		if (animate.getElapsedTime().asSeconds() > 0.15)
		{
			currentFrame = (currentFrame + 1) % 8;
			animate.restart();
		}

	}

	//virtual void checkPlantCollision(Zombie** zombie, int numofZomb)
	//{
	//	exist = bullet.checkcollision(zombie, numofZomb);
	//}


	void shoot(RenderWindow& window) ////////shooting projectile
	{
		Vector2f temp = position;
		temp.x += 45;
		temp.y += 7;
		if (bullet.getPosition().x == 0)
			bullet.setPositon(temp);
		else if (bullet.getPosition().x >= 960)
		{
			exist = false;
			bullet.setPositon(temp);
			if (bulletTime.getElapsedTime().asSeconds() > 4)
			{
				exist = true;
				bulletTime.restart();
			}
		}
		if (exist)
			bullet.move(window);

	}
};

class Repeater : public Plant 
{
private:
	IntRect animationFrames[5];
	int currentFrame;
	Projectile bullet;
	Projectile bullet2;
	Clock bulletTime2;
	bool exist1 = true;
	bool exist2 = true;

public:

	Repeater(int x, int y) : bullet(3, 3, "../PZ_Project/PVZ/Plants/pea.png", plantSprite.getPosition()), bullet2(8, 6, "../PZ_Project/PVZ/Plants/pea.png", plantSprite.getPosition())
	{
		position.x = x;
		position.y = y;
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/repeater3.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);
		row = (y - 174) / 98;


		int frameWidth = 35, frameHeight = 31;
		for (int i = 0; i < 5; ++i)
		{
			animationFrames[i] = IntRect(i * frameWidth, 0, frameWidth, frameHeight);
		}

		currentFrame = 0;
		health = 1000;

	}

	virtual void draw(RenderWindow& window)
	{
		plantSprite.setTextureRect(animationFrames[currentFrame]);

		plantSprite.setPosition(position.x, position.y);
		window.draw(plantSprite);

		if (animate.getElapsedTime().asSeconds() > 0.17)
		{
			currentFrame = (currentFrame + 1) % 5;
			animate.restart();
		}
	}

	/*virtual void checkPlantCollision(Zombie** zombie, int numofZomb)
	{
		exist1 = bullet.checkcollision(zombie, numofZomb);
	}*/


	void shoot(RenderWindow& window)
	{
		Vector2f temp = position;
		temp.x += 45;
		temp.y += 7;

		if (exist1)
		{
			if (bullet.getPosition().x == 0)
				bullet.setPositon(temp);
			else if (bullet.getPosition().x >= 960)
			{
				exist1 = false;
				bullet.setPositon(temp);
				if (bulletTime.getElapsedTime().asSeconds() > 2)
				{
					exist1 = true;
					bulletTime.restart();
				}
			}
			bullet.move(window);
		}



		if (bulletTime.getElapsedTime().asSeconds() > 0.1)
		{
			if (exist2)
			{
				if (bullet2.getPosition().x == 0)
					bullet2.setPositon(temp);
				else if (bullet2.getPosition().x >= 960)
				{
					exist2 = false;
					bullet2.setPositon(temp);
					if (bulletTime2.getElapsedTime().asSeconds() > 2)
					{
						exist2 = true;
						bulletTime2.restart();
					}
				}
				bullet2.move(window);
			}
		}
	}
};


class Sunflower : public Plant
{

private:

	IntRect animationFrames[6];
	int currentFrame;
	bool existSun;
public:

	Sunflower(int x, int y)
	{
		cout << "sunflower creating\n";
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/Sunflower3.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);
		existSun = false;
		position.x = x;
		position.y = y;
		int frameWidth = 30;
		for (int i = 0; i < 6; ++i)
		{
			animationFrames[i] = IntRect(i * frameWidth, 0, frameWidth, 31);
		}

		currentFrame = 0;
		cout << "sunflower created\n";
		row = (y - 174) / 98;

		health = 1000;
	}


	void draw(RenderWindow& window)
	{
		plantSprite.setTextureRect(animationFrames[currentFrame]);

		plantSprite.setPosition(position.x, position.y);
		window.draw(plantSprite);


		if (animate.getElapsedTime().asSeconds() > 0.1)
		{
			currentFrame = (currentFrame + 1) % 6;
			animate.restart();
		}
	}
	void shoot(RenderWindow& window)
	{
		if (existSun == false)
		{
			existSun = true;
		}
		else
			Sun(position.x + 40, position.y).draw(window);

	}
	Vector2f getPosition()
	{
		return plantSprite.getPosition();
	}
};

class Wallnut : public Plant
{
private:
	IntRect animationFrames[5];
	int currentFrame;
	bool exist = true;
	Texture rollingTexture;
	Sprite rollingSprite;
	IntRect movingAnimation[8];
	int currentMovingFrame;
	int isRolling;
	Clock rollingTime;
	
public:
	Wallnut(int x, int y) 
	{

		position.x = x;
		position.y = y;
		row = (y - 174) / 98;
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/wallnut3.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);

		int frameWidth = 27, frameHeight = 31;
		for (int i = 0; i < 5; ++i)
		{
			animationFrames[i] = IntRect(i * frameWidth, 0, frameWidth, frameHeight);
		}

		currentFrame = 0;

		rollingTexture.loadFromFile("../PZ_Project/PVZ/Plants/wallnut2.png");
		rollingSprite.setTexture(rollingTexture);
		rollingSprite.setScale(2.0f, 2.0f);

		for (int i = 0; i < 8; ++i)
		{
			movingAnimation[i] = IntRect(i * frameWidth+2*i, 0, frameWidth, frameHeight+2);
		}

		currentMovingFrame = 0;
		isRolling = true;
		health = 1000;

	}

	virtual void draw(RenderWindow& window)
	{
		if (!isRolling)
		{
			plantSprite.setTextureRect(animationFrames[currentFrame]);

			plantSprite.setPosition(position.x, position.y);
			window.draw(plantSprite);

			if (animate.getElapsedTime().asSeconds() > 0.17)
			{
				currentFrame = (currentFrame + 1) % 5;
				animate.restart();
			}
		}
		else
		{
			rollingSprite.setTextureRect(movingAnimation[currentMovingFrame]);

			rollingSprite.setPosition(position.x, position.y);
			window.draw(rollingSprite);
			if(position.x>960)
				isExist=false;

			if (rollingTime.getElapsedTime().asSeconds() > 0.17)
			{	
				position.x += 10;
				currentMovingFrame = (currentMovingFrame + 1) % 8;
				rollingTime.restart();
			}
		}
	}

	void shoot(RenderWindow& window)
	{
		

	}
};

class Cherrybomb : public Plant
{
private:
	IntRect animationFrames[6];
	int currentFrame;
	bool exist = true;

public:
	Cherrybomb(int x, int y) 
	{

		position.x = x;
		position.y = y;
		plantTexture.loadFromFile("../PZ_Project/PVZ/Plants/cherrybomb.png");
		plantSprite.setTexture(plantTexture);
		plantSprite.setScale(2.0f, 2.0f);

		animationFrames[0] = IntRect(0, 0, 34, 36);
		animationFrames[1] = IntRect(34+0, 0, 35, 36);
		animationFrames[2] = IntRect(115-46, 0, 46, 36);
		animationFrames[3] = IntRect(161-46, 0, 46, 36);
		animationFrames[4] = IntRect(212-50, 0, 50, 36);
		animationFrames[5] = IntRect(263-51, 0, 51, 36);
		
		row = (y - 174) / 98;

		currentFrame = 0;
		health = 1000;

	}

	virtual void draw(RenderWindow& window)
	{
		plantSprite.setTextureRect(animationFrames[currentFrame]);

		plantSprite.setPosition(position.x, position.y);
		window.draw(plantSprite);

		if (animate.getElapsedTime().asSeconds() > 0.6)
		{
			currentFrame = (currentFrame + 1) % 6;
			animate.restart();
		}

	}

	void shoot(RenderWindow& window)
	{
	

	}
};

class PlantFactory
{
public:

	Plant** plants;
	int index;
	PlantFactory()
	{
		plants = new Plant * [45] {nullptr};
		index = 0;
	}

	/////creating plant based upon user input
	void createPlant(int index, int type, int x, int y)
	{
		this->index++;
		if (type == 1)
			plants[index] = new Peashooter(x, y);
		else if (type == 2)
			plants[index] = new Sunflower(x, y);
		else if (type == 3)
			plants[index] = new Snowpea(x, y);
		else if (type == 4)
			plants[index] = new Repeater(x, y);
		else if (type == 5)
			plants[index] = new Wallnut(x, y);
		else if (type == 6)
			plants[index] = new Cherrybomb(x, y);
	}


	void finishPlant()
	{
		for (int i = 0; i < index; i++)
		{
			if (plants[i]->getHealth() <= 0)
			{
				plants[i]->setExist(false);
				
			}
		}
	}


	void draw(RenderWindow& window, int number)
	{

		if (plants[number] != nullptr && plants[number]->isExist)
		{
			plants[number]->draw(window);
			plants[number]->shoot(window);
			finishPlant();
		}
	}
	

	/*void checkCollision(Zombie** zombie, int numofZomb)
	{
		for (int i = 0; i < 45; i++)
		{
			if (plants[i] != nullptr && plants[i]->isExist)
			{
				for (int j = 0;j < 5;j++)
				{
					plants[i]->checkPlantCollision(zombie, numofZomb);
				}
			}
		}
	}*/



	Vector2f getUpdatedLocation()
	{
		for (int i = 0; i < index; i++)
		{
			if (plants[i] != nullptr)
			{
				if (!plants[i]->isExist)
				{
					return(  plants[i]->getPosition());
				}
			}
		}

	}
	int getUpdatedLocationY()
	{
		for (int i = 0; i < index; i++)
		{
			if (plants[i] != nullptr)
			{
				if (!plants[i]->isExist)
				{
					return ((plants[i]->getPosition().y - 174) / 98);
				}
				else return -1;
			}
		}

	}


	int getIndex()
	{
		return index;
	}

	~PlantFactory()
	{
		for (int i = 0; i < index; i++)
		{
			delete plants[i];
		}
		delete[] plants;
	}


};