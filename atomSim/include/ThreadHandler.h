#ifndef THREADHANDLER_H_INCLUDED
#define THREADHANDLER_H_INCLUDED


#include <SFML/Graphics.hpp>


#include "AtomWrapper.h"

class ThreadHandler
{
public:
    ThreadHandler();



private:
    AtomWrapper a;                                                                  //container for game data
    sf::RenderWindow window;                                                        //game window

    float WWidth = 1480.f, WHeight = 960.f, XPos = 200.f, YPos = 200.f;             //window data
    bool paused;                                                                    //gamestate

    bool mouseAttract;                                                              //
    bool mouseRepel;                                                                //
    float mouseAttractIntensity;
    float mouseRepelIntensity;
    sf::Text text;
};

#endif // THREADHANDLER_H_INCLUDED
