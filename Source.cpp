#include <iostream>
#include <SFML/Graphics.hpp>
#include "Header.h"
#include <ctime>
using namespace sf;
using namespace std;

int main()
{ 
    Plant* plant = new Peashooter();// Create a Peashooter object


    RenderWindow window(VideoMode(1366, 768), "SFML Window");

    // Set game icon
    Image icon;
    if (!icon.loadFromFile("../PZ_Project/Images/logo2.png")) { return 1; }
    window.setIcon(857, 769, icon.getPixelsPtr());
    
    // Constants for game grid
    const int Rows = 5;  // Number of rows in the grid
    const int Cols = 9;  // Number of columns in the grid
    const int Cell_Size_X = 80;  // Size of each cell (square) on the lawn
    const int Cell_Size_Y = 98;  // Size of each cell (square) on the lawn
    bool Field_Status[Rows][Cols] = { false };  // Array to track if a cell is occupied by a Peashooter

    // Diversion Pixels from top and left
    const int Diversion_X = 260;
    const int Diversion_Y = 174;
    // Clocks for timing
    Clock timeMoney;
    Clock clock;

    while (window.isOpen())
    {
        // Calculate time
        float time = clock.getElapsedTime().asMicroseconds();
        float moneyTime = timeMoney.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;

        createBack(window);

        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                // Get mouse position
                int mouseX = Mouse::getPosition(window).x;
                int mouseY = Mouse::getPosition(window).y;

                int tempX = (mouseX - Diversion_X);
                int tempY = (mouseY - Diversion_Y);
                if (tempX > 0 && tempY > 0)
                {

                    int gridX = (mouseX - Diversion_X) / Cell_Size_X;  // Adjust for grid offset and cell size
                    int gridY = (mouseY - Diversion_Y) / Cell_Size_Y;  // Adjust for grid offset, top bar, and cell size

                    // Check if the grid coordinates are valid and the cell is empty
                    if ((gridX >= 0 && gridX < Cols && gridY >= 0 && gridY < Rows) && (!Field_Status[gridY][gridX]))
                    {
                        Field_Status[gridY][gridX] = true;
                        plant->draw(window, Diversion_X + gridX * Cell_Size_X, Diversion_Y + gridY * Cell_Size_Y);  // Draw Peashooter at the grid position
                    }
                }
            }
        }
        //checking my grid 

        printGrid(Field_Status, Rows, Cols);

       for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Cols; ++j)
            {
                if (Field_Status[i][j])
                {
                    plant->draw(window, Diversion_X + j * Cell_Size_X, Diversion_Y + i * Cell_Size_Y);
                }
            }
        }
        window.display();
    }

    delete plant;
    return 0;
}