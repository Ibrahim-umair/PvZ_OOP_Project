#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;




class Sun
{
protected:
	Texture sunTexture;
	Sprite sunSprite;
	Vector2f position;
	bool exist;
	Clock beforeStart;
	int beforeStartSeconds;
	int currentFrame;
public:
	Sun()
	{
		position.x = rand() % 700 + 260;
		position.y = rand() % 200 + 184;
		sunTexture.loadFromFile("../PZ_Project/PVZ/Plants/sun2.png");
		sunSprite.setTexture(sunTexture);
		sunSprite.setScale(2.0f, 2.0f);
		IntRect texture(0, 0, 26, 26);
		sunSprite.setTextureRect(texture);

	}
	Sun(int x, int y)
	{

		sunTexture.loadFromFile("../PZ_Project/PVZ/Plants/sun2.png");
		sunSprite.setTexture(sunTexture);
		sunSprite.setScale(2.0f, 2.0f);
		IntRect texture(0, 0, 26, 26);
		sunSprite.setTextureRect(texture);

		position.x = x;
		position.y = y;
	}

	void setBeforeStart(int n)
	{
		beforeStart.restart();
		beforeStartSeconds =n;
	}
	bool isThere()
	{
		return exist;
	}
	void draw(RenderWindow& window)
	{
		if(beforeStart.getElapsedTime().asSeconds() < beforeStartSeconds)
			return;
		sunSprite.setTexture(sunTexture);
		sunSprite.setScale(2.0f, 2.0f);
		IntRect texture(0, 0, 26, 26);
		sunSprite.setTextureRect(texture);

		sunSprite.setPosition(position.x, position.y);
		window.draw(sunSprite);

		

	}
};

class SunFactory
{

public:

	Sun suns[5];

	SunFactory()
	{
		for (int i = 0; i < 5; i++)
		{
			suns[i] = Sun();
			suns[i].setBeforeStart( (i+1)*5);
		}
	}

	void draw(RenderWindow& window)
	{
		for (int i = 0; i < 5; i++)
		{
			suns[i].draw(window);
		}
	}
	
};