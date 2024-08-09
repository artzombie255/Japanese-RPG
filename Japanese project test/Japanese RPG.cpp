#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Level.h"
#include "DoubleSubscriptedArray.h"
#include "Npc.h"
#include "Enemy.h"
#include "Encounter.h"
#include "Intaractable.h"


const int WINDOWX = 600, WINDOWY = 600, NUMOFCHUNKS = 24, SIZEOFCHUNK = 25;

//probably get rid of
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
    Encounter encounter;
    int xScreen = 1, yScreen = 1;
    DoubleSubscriptedArray arr(NUMOFCHUNKS, NUMOFCHUNKS);
    std::vector<Intaractable*> Npcs;
    std::vector<Intaractable*> Enemies;
    bool inMenu = false;
    
    //create entities
    for (int i = 0; i < 6; i++)
        Npcs.push_back(new Npc(i));

    for (int i = 0; i < 6; i++)
        Enemies.push_back(new Enemy(1));

    //set up doing tect and window name
    font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
    hdr = L"日本語プロジェクト";
    text.setFont(font);
    //make window
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), hdr);

    window.setFramerateLimit(60);

    //load the first level
    level.loadLevel(arr, "./Levels/1level1");


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

            //encounter
            if (encounter.getInEncounter() == true)
                encounter.playEncounter(window);
        }

        inMenu = false;
        //sets if in esc menu
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
                inMenu = true;
        }
        if (player.getEscMenuOpen() == true)
            inMenu = true;

        //sets if in encounter
        for (int i = Enemies.size() - 1; i >= 0; i--)
        {
            if (Enemies.at(i)->getInteraction() == true)
            {
                encounter.setEncounter();
                Enemies.at(i)->setInteraction(false);
            }
        }

        //check collisions
        //move the player
        if (inMenu == false && encounter.getInEncounter() == false &&
            player.collision(Npcs, INTERACTIONTYPE::NPC) == false &&
            player.collision(Enemies, INTERACTIONTYPE::ENEMY) == false)
            player.move();

        //checks the screen the player is on
        if (xScreen != player.getScreenX() || yScreen != player.getScreenY())
        {
            std::cout << "switchLevel";
            xScreen = player.getScreenX();
            yScreen = player.getScreenY();
            level.loadLevel(arr, "./Levels/" + std::to_string(xScreen) + "level" + std::to_string(yScreen));
        }

        //prints the next window
        window.clear();

        level.print(window, arr);
        window.draw(player);

        //print npcs
        for (int i = Npcs.size() - 1; i >= 0; i--)
        {
            window.draw(*Npcs.at(i));
        }

        for (int i = Enemies.size() - 1; i >= 0; i--)
        {
            window.draw(*Enemies.at(i));
        }


        //interactions with entities
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
                Npcs.at(i)->talk(window, i);
        }
        
        //display encounters
        if (encounter.getInEncounter() == true)
            encounter.displayEncounter(window);

        player.printEscMenu(window);
        window.display();
    }

    //clean up
    for (int i = Npcs.size() - 1; i >= 0; i--)
    {
        delete Npcs.at(i);
    }

    for (int i = Enemies.size() - 1; i >= 0; i--)
    {
        delete Enemies.at(i);
    }

    return 0;
}