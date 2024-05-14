#pragma once
#include <iostream>
#include "zombies.h"
#include "plants.h"
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <time.h>
using namespace std;
using namespace sf;


class Levels
{
protected:

	ZombieFactory zombiefactory;
	PlantFactory plantfactory;

public:

	Levels() : zombiefactory(), plantfactory() {}

	Vector2f getUpdatedLocation()//location of plant
	{
		return plantfactory.getUpdatedLocation();
	}
	/////zombie movement & collision
	virtual void moveZombies(RenderWindow& window, int DiversionY, int Cell_Size_Y,int &lives)
	{
		zombiefactory.checkPlantCollision(plantfactory.plants, plantfactory.index);
		zombiefactory.moveZombies(window, DiversionY, Cell_Size_Y, lives);
	}
	/////plant movement & collision
	virtual void draw(RenderWindow& window, int number)
	{
		//plantfactory.checkCollision(zombiefactory.zombies, zombiefactory.numofZomb);
		plantfactory.draw(window, number);
	}
	//////creating plant
	virtual void createPlant(int number, int type, int x, int y)
	{
		plantfactory.createPlant(number, type, x, y);
	}
	virtual int getIndex()
	{
		return plantfactory.getIndex();
	}
	


};