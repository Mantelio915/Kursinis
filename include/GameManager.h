#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <iostream>

#define FPS 60.f

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Asteroid.h"

class GameManager
{
    public:
        GameManager();
        void init();
        void tick();
        void render();
        virtual ~GameManager();


        std::vector<Entity*> vEntities;
        std::vector<Bullet*> vBullets;
        std::vector<Asteroid*> vAsteroids;
        std::vector<sf::Texture*>vTextures;
        std::vector<Enemy*> vEnemies;
        sf::RenderWindow win;
        Player* playerP = nullptr;
    protected:

    private:

        sf::Clock fpsClock;
        sf::View view = sf::View(sf::Vector2f(0,0),sf::Vector2f(800,600));
        void collide();

        sf::Text hpText;
        sf::RectangleShape hpBar;
        sf::Font arialFont;


};

#endif // GAMEMANAGER_H
