#include "Asteroid.h"
#include "GameManager.h"

Asteroid::Asteroid(int x, int y, GameManager* gPtr)
{
    //Set the game manager object pointer.
    gP = gPtr;
    //Add the asteroid to asteroid vector.
    gP->vAsteroids.push_back(this);
    //Set the asteroid's sprite texture to the first texture of the texture vector.
    spr.setTexture(*gP->vTextures[0]);
    //Randomly choose from 3 different possible sprite looks, and select an appropriate rectangular part of the texture.
    switch(rand()%2)
    {
    case 0:
        spr.setTextureRect(sf::IntRect(20,0,18,17));
        break;
    case 1:
        spr.setTextureRect(sf::IntRect(38,0,17,15));
        break;
    case 2:
        spr.setTextureRect(sf::IntRect(55,0,17,17));
        break;
    default:
        break;
    }

    //Set sprite position
    spr.setPosition(x,y);

}

void Asteroid::update()
{

}
