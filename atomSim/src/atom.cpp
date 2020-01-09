#include "atom.h"
#include <stdlib.h>


inline float sqr(float x)
{
    return x*x;
}

inline sf::Vector2f vib(float speed)
{
    if(speed < 1)
        return sf::Vector2f(0, 0);

    float tempx = rand() % (static_cast<int>(20 * speed)) / 10 - speed;
    float tempy = sqrt(sqr(speed) - sqr(tempx));
    if(rand()%2 == 1)
        tempy = -tempy;
    return sf::Vector2f(tempx, tempy);
}

atom::atom(float x = 0, float y = 0)
{
    circle.setRadius(25);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(10, 10);
    move = sf::Vector2f(0, 0);

    vibrateSpeed = 10.0f;
    vibrateTick = sf::seconds(0);
    vibrate = vib(vibrateSpeed);
    circle.setPosition(x, y);

    circle.setFillColor(sf::Color(rand()%128+128, rand()%128+128, rand()%128+128));
}

atom::~atom()
{
    //dtor
}

void atom::tick(sf::Time dt)
{
    //update vibrate
    vibrateTick += dt;
    if(vibrateTick >= vibrateReset)
    {
        vibrate = vib(vibrateSpeed);
        vibrateTick = sf::seconds(0);
    }

    //relocate
    circle.move(vibrate * dt.asSeconds());

    circle.move(move * dt.asSeconds());
}
