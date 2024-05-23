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
#include "Intaractable.h"


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
    std::vector<Intaractable*> Npcs;
    bool inMenu = false;
    
    //create npcs
    for (int i = 0; i < 6; i++)
        Npcs.push_back(new Npc(i));

    //set up doing tect and window name
    font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
    hdr = L"日本語プロジェクト";
    text.setFont(font);
    //make window
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), hdr);

    window.setFramerateLimit(60);

    //load the first level
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

            //checks the player movement
            player.moveCheck();
            //opens the esc menu
            player.escMenu(window);

            //click to keep talking
            for (int i = 0; Npcs.size() > i; i++)
            {
                if (player.getEscMenuOpen() == false)
                    Npcs.at(i)->continueTalking(window);
            }
        }

        inMenu = false;
        //sets if in menu
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
                inMenu = true;
        }
        if (player.getEscMenuOpen() == true)
            inMenu = true;


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

        //move the player
        if (inMenu == false)
            player.move();

        //check collisions
        player.collision(Npcs, INTERACTIONTYPE::NPC);

        //prints the next window
        window.clear();

        window.draw(player);
        level.print(window, arr);
        //print npcs
        for (int i = Npcs.size() - 1; i >= 0; i--)
        {
            window.draw(*Npcs.at(i));
        }
        //interactions with npcs
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
                Npcs.at(i)->talk(window, i);
        }
        player.printEscMenu(window);
        window.display();
        window.clear();
    }

    //clean up
    for (int i = Npcs.size() - 1; i >= 0; i--)
    {
        delete Npcs.at(i);
    }

    return 0;
}