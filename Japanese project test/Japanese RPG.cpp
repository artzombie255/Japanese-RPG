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
#include "globals.h"


const int WINDOWX = 600, WINDOWY = 600, NUMOFCHUNKS = 24, SIZEOFCHUNK = 25;


int main()
{
    srand(time(NULL));

    //create everything
    sf::View viewport;
    sf::Font font;
    sf::String hdr;
    sf::Text text;
    Player player;
    Level level;
    Encounter encounter;
    int xScreen = 1, yScreen = 3, enemyEncounterNum = 0, enemySpawn = 0;
    DoubleSubscriptedArray arr(NUMOFCHUNKS, NUMOFCHUNKS);
    std::vector<Intaractable*> Npcs;
    std::vector<Intaractable*> Enemies;
    std::vector<Intaractable*> wallVec;
    bool inMenu = false, printWalls = false, addedCharacter[4] = {};

    viewport.setSize(600, 600);
    viewport.setCenter(300, 1500);

    //create entities
  
    Npcs.push_back(new Npc(BLANK));
    Npcs.push_back(new Npc(AERYK));
    Npcs.push_back(new Npc(AUBREY));
    Npcs.push_back(new Npc(ROWAN));
    Npcs.push_back(new Npc(BOOK));

    //for (int i = 0; i < 1; i++)


    //set up doing tect and window name
    font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
    hdr = L"日本語プロジェクト";
    text.setFont(font);
    //make window
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), hdr);
    window.setView(viewport);

    window.setFramerateLimit(60);

    //load the first level
    level.loadLevel(arr, "1level3", wallVec, 1, 3, viewport);

    level.addWalls(4);
    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(5400, 7));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, -600);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(5400, 7));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, 4793);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(7, 5400));
    wallVec.at(wallVec.size() - 1)->setPosition(2993, -600);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(7, 5400));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, -600);

    /*for (int i = 0; i <= wallVec.size() - 1; i++)
    {
        wallVec.push_back(new Intaractable);
        wallVec.at(i) = level.getWalls(i);
    }*/

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
            {
                viewport.setCenter(300, 300);
                encounter.playEncounter(window);
                if (encounter.endEncounter() == true)
                {
                    if (Enemies.size() - 1 != enemyEncounterNum)
                    {
                        for (int i = enemyEncounterNum; i < Enemies.size(); i++)
                        {
                            Enemies.at(i - 1) = Enemies.at(i);
                        }
                    }
                    Enemies.pop_back();

                }
            }
            else
            {
                std::cout << "out of enmcopnter\n";
                viewport.setCenter((600.f * player.getScreenX()) - 300, (600.f * player.getScreenY()) - 300);
                if (rand() % 1800 + 600 <= enemySpawn && addedCharacter[0] == true)
                {
                    Enemies.push_back(new Enemy(1, xScreen, yScreen));
                    enemySpawn = 0;
                }
                else
                    enemySpawn++;
            }

            window.setView(viewport);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                printWalls = true;
                window.setFramerateLimit(240);
            }
            else
            {
                printWalls = false;
                window.setFramerateLimit(60);
            }

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
                enemyEncounterNum = i;
                encounter.setEncounter();
                Enemies.at(i)->setInteraction(false);
            }
        }
  

        //check collisions
        //move the player
        if (inMenu == false && encounter.getInEncounter() == false &&
            player.collision(Npcs, INTERACTIONTYPE::NPC) == false &&
            player.collision(Enemies, INTERACTIONTYPE::ENEMY) == false &&
            player.collision(wallVec, INTERACTIONTYPE::WALL) == false
            )
        {
            player.move();
        }
        if (inMenu == false && encounter.getInEncounter() == false)
            for (int i = 0; i < Enemies.size(); i++)
            {
                Enemies.at(i)->move(player.getPosition().x, player.getPosition().y, wallVec);
            }

        //checks the screen the player is on
        if (xScreen != player.getScreenX() || yScreen != player.getScreenY())
        {
            /*for (int i = wallVec.size() - 1; i > 0; i--)
            {
                delete wallVec.at(i);
            }*/
            //wallVec.clear();
            std::cout << "switchLevel";
            xScreen = player.getScreenX();
            yScreen = player.getScreenY();
            level.loadLevel(arr, std::to_string(xScreen) + "level" + std::to_string(yScreen), wallVec, xScreen, yScreen, viewport);
            window.setView(viewport);
            /*for (int i = 0; i <= wallVec.size() - 1; i++)
            {
                wallVec.push_back(new Intaractable);
                wallVec.at(i) = level.getWalls(i);
            }*/
        }

        //prints the next window
        window.clear();

        level.print(window, arr);
        for (int i = 0; i < Enemies.size(); i++)
        {
            //window.draw(*Enemies.at(i));
            Enemies.at(i)->print(window);
        }

        if (printWalls == true)
            for (int i = wallVec.size() - 1; i >= 0; i--)
                window.draw(*wallVec.at(i));

        window.draw(player);


        //print npcs
        for (int i = Npcs.size() - 1; i >= 0; i--)
        {
            Npcs.at(i)->print(window);
        }

        for (int i = Enemies.size() - 1; i >= 0; i--)
        {
            Enemies.at(i)->print(window);
        }

        level.printF(window, arr);

        //interactions with entities
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
            {
                Npcs.at(i)->talk(window, xScreen, yScreen);
                //std::cout << Npcs.at(i)->getCurrentInteraction();
             

            }
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 1)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 2)
        {
            level.updateRoom(1, 1);
            Npcs.at(1)->setPosition(-1000, -1000);
            Npcs.at(1)->setSize(sf::Vector2f(0, 0));
            Npcs.at(2)->setPosition(-1000, -1000);
            Npcs.at(2)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setSize(sf::Vector2f(1200, 25));
            Npcs.at(0)->setPosition(-300, 3000);
            if (addedCharacter[0] == false)
            {
                encounter.addToTeam(CHARACTERS::AUBREY);
                addedCharacter[0] = true;
            }
            if (addedCharacter[1] == false)
            {
                encounter.addToTeam(CHARACTERS::AERYK);
                addedCharacter[1] = true;
            }
        }
        
        if (Npcs.at(0)->getCurrentInteraction() >= 3)
        {
            Npcs.at(0)->setSize(sf::Vector2f(500, 600));
            Npcs.at(0)->setPosition(1870, -600);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 4)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
            Npcs.at(3)->setPosition(2210, -157);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 5)
        {   
            Npcs.at(4)->setSize(sf::Vector2f(25, 25));
            Npcs.at(4)->setPosition(2210, 2100);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 6)
        {
            Npcs.at(4)->setSize(sf::Vector2f(0, 0));
            Npcs.at(4)->setPosition(-1000, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 7)
        {
            Npcs.at(3)->setSize(sf::Vector2f(0, 0));
            Npcs.at(3)->setPosition(-1000, -1000);
            if (addedCharacter[2] == false)
            {
                encounter.addToTeam(CHARACTERS::ROWAN);
                addedCharacter[2] = true;
            }
            Npcs.at(0)->setSize(sf::Vector2f(600, 600));
            Npcs.at(0)->setPosition(0, 3100);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 8)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
        }

        //std::cout << "x: " << xScreen << "\ny: " << yScreen << "\n";
        std::cout << level.getInCave();

        for (int i = 0; i < 4; i++)
        {
            //encounter.printTeamSpot(i);
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

    for (int i = wallVec.size() - 1; i >= 0; i--)
    {
        delete wallVec.at(i);
    }
    return 0;
}