#include "Player.h"
#include "GameManager.h"
#include "Bullet.h"
#include <math.h>

Player::Player(int x, int y, GameManager* managerP)
{
    //Initial creation of the player sprite and setting it to a portion of the Texture file
    spr.setPosition(x,y);
    spr.setTextureRect(sf::IntRect(0,0,16,16));
    gP = managerP;
}

void Player::update()
{
    //Input handling
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        spr.move(0,-3);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        spr.move(0,3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        spr.move(-3,0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        spr.move(3,0);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && firingClock.getElapsedTime().asMilliseconds()>500)
    {
        //Resetting of the firing clock, after checking if it has been 500 milliseconds since last time a bullet was fired.
        firingClock.restart();
        //We map the mouse coordinates relative to the window to relative to the game world, then subtract the player position.
        sf::Vector2f toMouse = (sf::Vector2f)gP->win.mapPixelToCoords(sf::Mouse::getPosition(gP->win)) - spr.getPosition();
        //We obtain the length of the vector with pythagoras theorem
        float lgt =    sqrt(
                            (float)pow(toMouse.x,2)+
                            (float)pow(toMouse.y,2));
        //Finally we normalize the vector by diving it by it's length.
        toMouse.x/=lgt;
        toMouse.y/=lgt;

        //We create a new bullet and add it to gamemanagers bullets vector.
        gP->vEntities.push_back(new Bullet( spr.getPosition().x,
                                            spr.getPosition().y,
                                           toMouse.x,
                                           toMouse.y,
                                            gP,this));

    }
}

Player::~Player()
{
    //dtor
}
