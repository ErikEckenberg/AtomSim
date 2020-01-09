#define _USE_MATH_DEFINES
#include <SFML/System.hpp>
#include <SFML/Graphics/Font.hpp>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include "ThreadHandler.h"



ThreadHandler::ThreadHandler()
{

    srand(time(NULL));

    window.create(sf::VideoMode(WWidth, WHeight), "Atom Simulator");
    sf::Mouse::setPosition(sf::Vector2i(WWidth/2, WHeight/2), window);
    window.setPosition(sf::Vector2i(XPos, YPos));
    window.setKeyRepeatEnabled(false);

    sf::Font font;
    font.loadFromFile("calibri.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setPosition(WWidth-100, 10);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Green);


    sf::Clock   deltaClock,                         //gameclock
                displayTimeClock;                   //independent clock only used for framecounting

window.create(sf::VideoMode(WWidth, WHeight), "Atom Simulator");

    a.create(150, &window);

    paused = false;
    mouseAttract = false;
    mouseRepel = false;

    mouseAttractIntensity = 0.1f;
    mouseRepelIntensity = 0.1f;


    while (window.isOpen())
    {
        window.clear();
        //handle events

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                ;

            if (event.type == sf::Event::GainedFocus)
                ;


            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    paused = !paused;
                }
                else if(event.key.code == sf::Keyboard::LControl)
                {
                    a.setResistance(0.99999);
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::LControl)
                {
                    a.resetResistance();
                }
            }



            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    mouseAttract = !mouseAttract;
                    if(mouseAttract)
                        mouseRepel = false;
                }

                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    mouseRepel = !mouseRepel;
                    if(mouseRepel)
                        mouseAttract = false;
                }
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    mouseRepel = false;
                    mouseAttract = false;
                    mouseRepelIntensity = 1;
                    mouseAttractIntensity = 1;
                }

            }

            if(event.type == sf::Event::MouseWheelScrolled)
            {
                if(mouseRepel)
                    mouseRepelIntensity *= pow(1.1, event.mouseWheelScroll.delta);
                if(mouseAttract)
                    mouseAttractIntensity *= pow(1.1, event.mouseWheelScroll.delta);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                    ;
                if(event.mouseButton.button == sf::Mouse::Right)
                    ;
            }

        }




        sf::Time dt = deltaClock.restart();




        //update screen
        if(!paused && window.hasFocus())
        {
            if(mouseAttract)
            {
                a.mouseAttract(dt, &window, mouseAttractIntensity);
            }
            if(mouseRepel)
            {
                a.mouseRepel(dt, &window, mouseRepelIntensity);
            }


            a.tick(dt, &window);

            //fps counter
            text.setString(std::to_string(static_cast<int>(1/dt.asSeconds())));
            window.draw(text);

            window.display();
        }

    }
}

