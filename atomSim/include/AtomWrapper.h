#ifndef ATOMWRAPPER_H
#define ATOMWRAPPER_H

#include <vector>
#include <utility>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "atom.h"

class atom;

class AtomWrapper
{
    public:
        AtomWrapper();
        AtomWrapper(int, sf::RenderWindow*);
        void create(int, sf::RenderWindow*);
        virtual ~AtomWrapper();
        void tick(sf::Time, sf::RenderWindow*);
        void mouseRepel(sf::Time, sf::RenderWindow*, float);
        void mouseAttract(sf::Time, sf::RenderWindow*, float);
        void setResistance(float r){resistance = r;};
        void resetResistance(){resistance = baseResistance;};

        void updateThread(const sf::Time*, sf::RenderWindow*, int i);

    protected:

    private:
        float resistance;                                               //natural slowdown of atoms due to
        float baseResistance;
        std::vector<atom> atomVec;
        std::pair<int, int> factors(int);
};

#endif // ATOMWRAPPER_H
