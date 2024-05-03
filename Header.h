#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

void createBack(RenderWindow& window)
{
	const int blackScreen = 84;

	Texture bgTexture;
	bgTexture.loadFromFile("../PZ_Project/PVZ/backgrounds/level1.png");
	Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, blackScreen);


	window.draw(bgSprite);
}

void printGrid(bool Field_Status[][9], const int Rows, const int Cols)
{
	// Print top border
	cout << "+";
	for (int i = 0; i < Cols; ++i)
	{
		cout << "---+";
	}
	cout << endl;
	// Print grid content
	for (int i = 0; i < Rows; ++i)
	{
		cout << "|";
		for (int j = 0; j < Cols; ++j) {
			char symbol = (Field_Status[i][j]) ? 'X' : ' ';
			cout << " " << symbol << " |";
		}
		cout << endl;

		// Print separator between rows
		cout << "+";
		for (int k = 0; k < Cols; ++k)
		{
			cout << "---+";
		}
		cout << endl;
	}
	cout << "\n\n\n";
}

struct coordinates
{
	int x;
	int y;
};

// Function to convert mouse coordinates to grid coordinates
coordinates getGridCoordinates(int mouseX, int mouseY, int Cell_Size_X, int Cell_Size_Y)
{
	coordinates coords;
	coords.x = (mouseX - 250) / Cell_Size_X;
	coords.y = (mouseY - 100 - 84) / Cell_Size_Y;
	return coords;
};



class Plant
{
protected:
	Sprite sprite;
public:
	virtual void draw(RenderWindow& window, int x, int y) = 0;
};

class Peashooter : public Plant
{


private:
	Texture peashooterTexture;
	IntRect spriteRect;  // Rect to define the portion of the texture to display
	

public:

	Peashooter()// : frameWidth(26), frameCount(8), currentFrame(0)
	{
		peashooterTexture.loadFromFile("../PZ_Project/PVZ/Plants/Peashooter2.png");
		sprite.setTexture(peashooterTexture);
		sprite.setScale(2.0f, 2.0f);
		spriteRect = IntRect(0, 0, 26, 32);
		sprite.setTextureRect(spriteRect);
	}
	

	void draw(RenderWindow& window, int x, int y) override
	{
		sprite.setPosition(x, y);
		window.draw(sprite);
	}
};

class Sunflower : public Plant
{
public:

	void draw(RenderWindow& window,int x, int y)
	{
		Texture sunflowerTexture;
		sunflowerTexture.loadFromFile("../PZ_Project/PVZ/Plants/sunflower2.png");
		sprite.setTexture(sunflowerTexture);
		sprite.setTextureRect(IntRect(100, 37, 30, 37));
		sprite.setScale(2.0f, 2.0f);
		sprite.setPosition(x, y);

		window.draw(sprite);
	}

	void animate()
	{}
};

class Wallnut : public Plant
{
public:

	void draw(RenderWindow& window, int x, int y)
	{
		Texture wallnutTexture;
		wallnutTexture.loadFromFile("../PZ_Project/PVZ/Plants/wallnut.png");
		sprite.setTexture(wallnutTexture);
		sprite.setTextureRect(IntRect(0, 0, 28, 32));
		sprite.setScale(2.0f, 2.0f);
		sprite.setPosition(x, y);

		window.draw(sprite);
	}
};

class Snowpea : public Plant
{
public:

	void draw(RenderWindow& window, int x, int y)
	{
		Texture snowpeaTexture;
		snowpeaTexture.loadFromFile("../PZ_Project/PVZ/Plants/snowpea.png");
		sprite.setTexture(snowpeaTexture);
		sprite.setTextureRect(IntRect(31, 0, 31, 31));
		sprite.setScale(2.0f, 2.0f);
		sprite.setPosition(x, y);
		window.draw(sprite);
	}
};
	
class Cherrybomb : public Plant
{
public:

	void draw(RenderWindow& window, int x, int y)
	{
		Texture cherrybombTexture;
		cherrybombTexture.loadFromFile("../PZ_Project/PVZ/Plants/cherrybomb.png");
		sprite.setTexture(cherrybombTexture);
		sprite.setTextureRect(IntRect(1, 10, 32, 27));
		sprite.setScale(2.0f, 2.0f);
		sprite.setPosition(x, y);

		window.draw(sprite);
	}
	void animate() {}
};



//That sounds like a solid plan! By using a PlantFactory class and composing the Plant objects within it using pointers, you can create multiple instances of plants for each placement in your game. This approach will allow you to manage each plant independently, which will be crucial for implementing actions like shooting or animations for individual plants in the future. If you need any further guidance on implementing this approach or have any questions, feel free to ask!
class PlantFactory
{
	Plant* plant;
	public:
		PlantFactory(Plant* plant) : plant(plant) {}
		void draw(RenderWindow& window, int x, int y)
		{
			plant->draw(window, x, y);
		}

};
