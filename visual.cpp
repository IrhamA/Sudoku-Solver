#include <SFML/Graphics.hpp> 
#include "solver.cpp"
#include <iostream>
#include <utility>
#include <unistd.h>

#include <chrono>
#include <thread>

using namespace sf;
using namespace std; 

// 1. Given a board show the output of the unsolved board for 4 seconds
// 2. Show the solution to the board afterwards 

// If you can figure this out
// 2. From here make a function that prints every entry we put in given (window, number, valid)
// using the backtracking solve function

//Global Variables
////////////////////////////////////////////////////////////////////////////////////////////////
RenderWindow window(sf::VideoMode(1000, 1000), "Sudoko Solver");    // We make a window class

////////////////////////////////////////////////////////////////////////////////////////////////

// drawText(window, text, valid)
//
// Everytime we want to draw a number on the board we call this function 
// we can draw the number and if it is wrongly place we will make it red
void drawText(RenderWindow * window, Text t, bool valid) {
    if (valid) { 
        t.setFillColor(Color::Red);
    }
    window->draw(t);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    // Load the texture file into the window
    Texture background;
    if (!background.loadFromFile("Grids/Sudoku Grid.png")) { 
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Load the font from a file
    Font font;
    if (!font.loadFromFile("Fonts/JMH Typewriter.ttf")) {
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Make a rectangle called board with dimensions (1000x1000)
    RectangleShape board(Vector2f(1000.f, 1000.f));
    // Set the color of board to be (E7,EC,E3)
    board.setFillColor(Color(0xE7,0xEC,0xE3));
    // Set the texture of the board to be the image
    board.setTexture(&background, true);
    window.draw(board);

    int b[9][9] = {
    {0,0,5,3,0,0,0,0,0},
    {8,0,0,0,0,0,0,2,0},
    {0,7,0,0,1,0,5,0,0},
    {4,0,0,0,0,5,3,0,0},
    {0,1,0,0,7,0,0,0,6},
    {0,0,3,2,0,0,0,8,0},
    {0,6,0,5,0,0,0,0,9},
    {0,0,4,0,0,0,0,3,0},
    {0,0,0,0,0,9,7,0,0}
    };

    int new_b[9][9] = {
    {0,0,5,3,0,0,0,0,0},
    {8,0,0,0,0,0,0,2,0},
    {0,7,0,0,1,0,5,0,0},
    {4,0,0,0,0,5,3,0,0},
    {0,1,0,0,7,0,0,0,6},
    {0,0,3,2,0,0,0,8,0},
    {0,6,0,5,0,0,0,0,9},
    {0,0,4,0,0,0,0,3,0},
    {0,0,0,0,0,9,7,0,0}
    };
    solve(new_b);
    
    float x = 40;
    float y = 10;
    // Represents the 9 rows
    for (int i = 0; i < 9; i++) {
        y = 10 + i*108;
        // Represents the 9 columns
        for (int j = 0; j < 9; j++) {
            x =  40 + j*108;
            Text text;
            text.setFont( font );

            //window.display();

            if (b[i][j] == 0) {
                text.setString( to_string(new_b[i][j]));
                text.setCharacterSize(100);
                text.setFillColor(Color::Blue);
                text.setPosition(x,y); 

                window.draw(text);                 

                continue;                
            }

            text.setString( to_string(b[i][j]));
            text.setCharacterSize(100);
            text.setFillColor(Color::Black);
            text.setStyle(Text::Bold);
            text.setPosition(x,y); 
            window.draw(text);   

        }
        x = 40;
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    window.display();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}