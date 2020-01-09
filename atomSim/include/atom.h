#ifndef ATOM_H
#define ATOM_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "AtomWrapper.h"

class AtomWrapper;

class atom
{
    public:
        atom();
        atom(float, float);
        virtual ~atom();
        void tick(sf::Time);
        sf::Vector2f getPosition(){return circle.getPosition();};
        float getRadius(){return circle.getRadius();};

        sf::Vector2f move;
        sf::CircleShape circle;

        friend class ::AtomWrapper;

    protected:

    private:


        sf::Vector2f vibrate;
        float vibrateSpeed;
        sf::Time vibrateTick;
        const sf::Time vibrateReset = sf::seconds(0.1f);


};

#endif // ATOM_H
