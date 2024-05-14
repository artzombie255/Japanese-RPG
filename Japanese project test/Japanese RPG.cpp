#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Level.h"
#include "DoubleSubscriptedArray.h"
#include "Npc.h"
#include "Encounter.h"


const int WINDOWX = 600, WINDOWY = 600, NUMOFCHUNKS = 24, SIZEOFCHUNK = 25;

enum class NPCS
{
    AUBREY,
    ASHTON,
    AERYK,
    LILLY,
    KIMORA,
    SHIN
};


int main()
{
    //create everything
    sf::Font font;
    sf::String hdr;
    sf::Text text;
    Player player;
    Level level;
    int xScreen = 1, yScreen = 1;
    DoubleSubscriptedArray arr(NUMOFCHUNKS, NUMOFCHUNKS);
    std::vector<sf::RectangleShape>* Npcs;
    

    font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
    hdr = L"日本語プロジェクト";
    text.setFont(font);
 
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), hdr);

    window.setFramerateLimit(60);

    level.loadLevel(arr, "./Levels/1level1.txt");

    //main loop
    while (window.isOpen())
    {
        //events go here
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            player.moveCheck();

            player.escMenu(window);
        }

        //checks player collisions

        //if enemy: encounter

        //if npc: talk

        //checks the screen the player is on
        if (xScreen != player.getScreenX() || yScreen != player.getScreenY())
        {
            std::cout << "switchLevel";
            xScreen = player.getScreenX();
            yScreen = player.getScreenY();
            level.loadLevel(arr, "./Levels/" + std::to_string(xScreen) + "level" + std::to_string(yScreen) + ".txt");
        }
        if (player.getEscMenuOpen() == false)
            player.move();

        player.collision(Npcs, 1);

        //prints the next window
        window.clear();

        window.draw(player);
        level.print(window, arr);
        player.printEscMenu(window);
        window.display();
        window.clear();
    }

    return 0;
}