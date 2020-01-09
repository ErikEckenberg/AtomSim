#include "AtomWrapper.h"

float pyth(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
std::pair<int, int> AtomWrapper::factors(int a)
{
    while(a)
    {
        int x = sqrt(a), y;

        for(; x ; x--)
        {
            y = a / x;
            if(2*x<y || abs(x-y) > 1)
                break;
            if(x * y == a)
                return std::make_pair(x, y);
        }
        a--;
    }
    return std::make_pair(0, 0);
}

AtomWrapper::AtomWrapper()
{
    baseResistance = 0.2;
    resistance = 0.2;
}

AtomWrapper::AtomWrapper(int amount, sf::RenderWindow *window)
{
    baseResistance = 0.2;
    resistance = 0.2;
    create(amount, window);
}

void AtomWrapper::create(int amount, sf::RenderWindow *window)
{
    std::pair<int, int> f = factors(amount);

    int SizeX = window->getSize().x/(f.first+1), SizeY = window->getSize().y/(f.second+1);

    for(int x = 1; x <= f.first; x++)
        for(int y = 1; y <= f.second; y++)
            atomVec.push_back(atom(SizeX*x, SizeY*y));
}

AtomWrapper::~AtomWrapper()
{
    //dtor
}

void AtomWrapper::mouseRepel(sf::Time dt, sf::RenderWindow *window, float intensity)
{
    for(size_t i = 0; i < atomVec.size(); i++)
    {
        float h = pyth(atomVec[i].getPosition(), sf::Vector2f(sf::Mouse::getPosition(*window)))/10.f;                //distance between current atom and mouse
        h = h > 0.2?h:0.2;
        sf::Vector2f p = (atomVec[i].getPosition() - sf::Vector2f(sf::Mouse::getPosition(*window))) / h;             //unit vector of distance between atoms
        atomVec[i].move += intensity / (h * h) * p;
    }
}

void AtomWrapper::mouseAttract(sf::Time dt, sf::RenderWindow *window, float intensity)
{
    for(size_t i = 0; i < atomVec.size(); i++)
    {
        float h = pyth(atomVec[i].getPosition(), sf::Vector2f(sf::Mouse::getPosition(*window)))/10.f;               //distance between current atom and mouse
        h = h > 0.2?h:0.2;
        sf::Vector2f p = (sf::Vector2f(sf::Mouse::getPosition(*window)) - atomVec[i].getPosition()) / h;            //unit vector of distance between atoms
        atomVec[i].move += intensity / (h * h) * p;
    }
}

void AtomWrapper::tick(sf::Time dt, sf::RenderWindow *window)
{
    #pragma omp parallel for
    for(size_t i = 0; i < atomVec.size(); i++)
    {
        //apply resistance
        atomVec[i].move = atomVec[i].move * static_cast<float>(pow(1-resistance, dt.asSeconds()));

        //calculate squared repulsion and cubed attraction
        for(size_t j = i+1; j < atomVec.size(); j++)
        {
            float   h  = pyth(atomVec[i].getPosition(), atomVec[j].getPosition())/10.f;        //distance between atoms
            float   c1 = 5.0,                                                                  //repulsion constant
                    c2 = 0.2;                                                                  //attraction constant

            sf::Vector2f p = (atomVec[i].getPosition() - atomVec[j].getPosition()) / h;         //unit vector of distance between atoms

            sf::Vector2f momentum = ((c1 - h * c2)/(h * h * h)) * p;

            atomVec[i].move += momentum;
            atomVec[j].move -= momentum;
        }

        //contain atoms within window
        if  ((atomVec[i].getPosition().x <= atomVec[i].getRadius() && atomVec[i].move.x < 0) ||
             (atomVec[i].getPosition().x >= window->getSize().x - atomVec[i].getRadius() && atomVec[i].move.x > 0))
             atomVec[i].move.x *= -1;

        if  ((atomVec[i].getPosition().y <= atomVec[i].getRadius() && atomVec[i].move.y < 0) ||
             (atomVec[i].getPosition().y >= window->getSize().y - atomVec[i].getRadius() && atomVec[i].move.y > 0))
             atomVec[i].move.y *= -1;



        atomVec[i].tick(dt);

        window->draw(atomVec[i].circle);
    }
}
