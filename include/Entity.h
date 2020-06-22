#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp"

//Forward declaration
class GameManager;
class Entity
{
    public:
        Entity();
        virtual ~Entity();
        virtual void update() = 0;
        //SFML sprite
        sf::Sprite spr;
        //Pointer to the game manager object.
        GameManager* gP = nullptr;
};

#endif // ENTITY_H
