
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "Header.h"
#include "plants.h"
#include "zombies.h"
#include "levels.h"
#include <ctime>
#include <cstdlib>
#include <time.h>
using namespace sf;
using namespace std;

int main()
{

    Levels level;


    RenderWindow window(VideoMode(1366, 768), "SFML Window");

    Image icon;
    if (!icon.loadFromFile("../PZ_Project/Images/logo2.png")) { return 1; }
    window.setIcon(857, 769, icon.getPixelsPtr());

    Texture bgTexture, peashooter, sunflower, snowpea, wallnut, cherrybomb, sun, repeater;
    bgTexture.loadFromFile("../PZ_Project/PVZ/backgrounds/level1.png");
    peashooter.loadFromFile("../PZ_Project/PVZ/Plants/card_peashooter.png");
    snowpea.loadFromFile("../PZ_Project/PVZ/Plants/card_snowpea.png");
    wallnut.loadFromFile("../PZ_Project/PVZ/Plants/card_wallnut.png");
    cherrybomb.loadFromFile("../PZ_Project/PVZ/Plants/card_cherrybomb.png");
    repeater.loadFromFile("../PZ_Project/PVZ/Plants/card_repeaterpea.png");
    sunflower.loadFromFile("../PZ_Project/PVZ/Plants/card_sunflower.png");

    Sprite peashooterSprite(peashooter);
    Sprite sunflowerSprite(sunflower);
    Sprite repeaterSprite(repeater);
    Sprite snowpeaSprite(snowpea);
    Sprite cherrybombSprite(cherrybomb);
    Sprite wallnutSprite(wallnut);

    const int Rows = 5;
    const int Cols = 9;
    const int Cell_Size_X = 80;
    const int Cell_Size_Y = 98;
    int Field_Status[Rows][Cols] = { false };

    const int Diversion_X = 260;
    const int Diversion_Y = 174;

    SunFactory suns;

    Texture homeTexture, mainTexture, lawnTexture;
    if (!homeTexture.loadFromFile("../PZ_Project/PVZ/backgrounds/homescreenpvz.jpg") ||
        !mainTexture.loadFromFile("../PZ_Project/PVZ/backgrounds/mainmenu.jpg") ||
        !lawnTexture.loadFromFile("../PZ_Project/PVZ/backgrounds/level1.png")) {
        cout << "Failed to load screen textures!" << endl;
        return 1;
    }
    Sprite homeSprite(homeTexture);
    Sprite mainSprite(mainTexture);
    Sprite lawnSprite(lawnTexture);


    Clock timeMoney;
    Clock clock;
    Clock Spawn;
    Clock gridClock;
    int count = 0;
    int index = 0;
    int type = 0;
    Vector2f emptySpot;
    Clock emptySpotClock;
    int X = 0, Y = 0;
    int sunsCollected = 1000;
    int lives = 3;
    while (window.isOpen())
    {
        window.clear();
        createBack(window, bgTexture);
        drawMenu(window, peashooterSprite, sunflowerSprite, repeaterSprite, snowpeaSprite, cherrybombSprite, wallnutSprite);
        displaySun(window, sunsCollected);
        displayLives(window, lives);
        // Calculate time
       
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {

            if (lives<=0 || event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Get mouse position
                int mouseX = Mouse::getPosition(window).x;
                int mouseY = Mouse::getPosition(window).y;
                
                //peashoooter
                if ((mouseX >= 80 && mouseX <= 130) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 1;
                    peashooterSprite.setScale(1.15f, 1.15f);
                }
                //sunflower
                else if ((mouseX >= 150 && mouseX <= 200) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 2;
                    sunflowerSprite.setScale(1.15f, 1.15f);
                }
                //snowpea
                else if ((mouseX >= 220 && mouseX <= 270) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 3;
                    snowpeaSprite.setScale(1.15f, 1.15f);
                }
                //repeater
                else if ((mouseX >= 290 && mouseX <= 340) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 4;
                    repeaterSprite.setScale(1.15f, 1.15f);
                }
                //  
                else if ((mouseX >= 360 && mouseX <= 410) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 5;
                    wallnutSprite.setScale(1.15f, 1.15f);
                }
                else if ((mouseX >= 430 && mouseX <= 480) && (mouseY >= 12 && mouseY <= 120))
                {
                    type = 6;
                    cherrybombSprite.setScale(1.15f, 1.15f);
                }
                
                if (type != 0 && type <= 6)
                {
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {

                        int mouseX2 = Mouse::getPosition(window).x;
                        int mouseY2 = Mouse::getPosition(window).y;
                        int tempX = (mouseX2 - Diversion_X);
                        int tempY = (mouseY2 - Diversion_Y);

                        if (tempX > 0 && tempY > 0)
                        {
                            int gridX = (mouseX - Diversion_X) / Cell_Size_X;
                            int gridY = (mouseY - Diversion_Y) / Cell_Size_Y;

                            if ((gridX >= 0 && gridX < Cols && gridY >= 0 && gridY < Rows) && (!Field_Status[gridY][gridX]))
                            {
                                if (event.mouseButton.button == Mouse::Left)
                                {

                                    Field_Status[gridY][gridX] = type;
                                    level.createPlant(index, type, Diversion_X + gridX * Cell_Size_X, Diversion_Y + gridY * Cell_Size_Y);
                                    index++;

                                    if(type == 2)
									{
										sunsCollected -= 50;
									}
									else if(type == 1)
									{
										sunsCollected -= 100;
									}
									else if(type == 3)
									{
										sunsCollected -= 175;
									}
									else if(type == 4)
									{
										sunsCollected -= 200;
									}
									else if(type == 5)
									{
										sunsCollected -= 50;
									}
									else if(type == 6)
									{
										sunsCollected -= 150;
									}

                                }
                            }
                        }
                    }
                }
            }
        }

        printGrid(Field_Status, Rows, Cols,gridClock);
        
        int maxIndex = 45;
        for (int i = 0; i < maxIndex; i++)
        {
            level.draw(window, i);
        }
        
        if(lives<=0)
            displayLoose(window);


      emptySpot= level.getUpdatedLocation();
        emptySpot.x = emptySpot.x - Diversion_X;
        emptySpot.y = emptySpot.y - Diversion_Y;
        int gridX = (emptySpot.x) / Cell_Size_X;
        int gridY = (emptySpot.y) / Cell_Size_Y;
        Field_Status[gridY][gridX] = 0;

    
        suns.draw(window);

        level.moveZombies(window, Diversion_Y, Cell_Size_Y,lives);
        window.display();

    }

    return 0;
}
