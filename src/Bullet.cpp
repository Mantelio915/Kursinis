#include "Bullet.h"
#include "GameManager.h"

Bullet::Bullet(int x, int y, float xm, float ym, GameManager* gPtr, Entity* owner)
{

    //Set the movement direction vector.
    vMov = sf::Vector2f(xm,ym);
    //Set the game manager pointer.
    gP = gPtr;
    //Add the bullet to the bullet vector.
    gP->vBullets.push_back(this);
    //Set the sprite to the first texture of texture vector.
    spr.setTexture(*gP->vTextures[0]);
    //Set the sprite to a rectangular part of the Texture.
    spr.setTextureRect(sf::IntRect(16,0,4,4));
    //Set position to the one given in arguments.
    spr.setPosition(x,y);
    //Set the firedBy Entity pointer.
    firedBy = owner;
}

void Bullet::update()
{
    //Move the bullet in it's fired direction.
    spr.move(vMov*15.f);
}

