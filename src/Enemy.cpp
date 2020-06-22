#include "Enemy.h"
#include "GameManager.h"
#include "Bullet.h"
#include <math.h>
Enemy::Enemy(int x, int y,  GameManager* gPtr)
{
    gP = gPtr;
    gP->vEnemies.push_back(this);
    spr.setTexture(*gP->vTextures[0]);
    spr.setTextureRect(sf::IntRect(72,0,17,17));
    spr.setPosition(x,y);
}

void Enemy::update()
{
    int playerDistance = sqrt(pow(gP->playerP->spr.getGlobalBounds().left - spr.getPosition().x,2)+
                              pow(gP->playerP->spr.getGlobalBounds().top  - spr.getPosition().y,2));
    int clock = firingClock.getElapsedTime().asMilliseconds();
    if(playerDistance < 300)
    {
        int a  = 123;
    }
    if(playerDistance < 300 && firingClock.getElapsedTime().asMilliseconds() > 1000)
    {
        firingClock.restart();


        sf::Vector2f toTarget = (sf::Vector2f)gP->playerP->spr.getPosition() - spr.getPosition();
        float lgt =    sqrt(
                            (float)pow(toTarget.x,2)+
                            (float)pow(toTarget.y,2));
        toTarget.x/=lgt;
        toTarget.y/=lgt;
        gP->vEntities.push_back(new Bullet( spr.getPosition().x,
                                            spr.getPosition().y,
                                           toTarget.x,
                                           toTarget.y,
                                            gP,this));
    }
}

Enemy::~Enemy()
{
    //dtor
}
