#include "GameManager.h"

GameManager::GameManager()
{
    //Create the SFML window.
    win.create(sf::VideoMode(800,600,32), "Manta Blaster");


    srand(time(0));

    //Create a new SFML texture and load it from file, then add it to a std::vector, for possibility of more textures being added.
    vTextures.push_back(new sf::Texture());
    if(!vTextures.back()->loadFromFile("res//textures.png"))
    {
        //Check if the texture loading failed.
        printf("Failed to load textures.png");
    }

    //Create a new player object, then add it to entity vector.
    playerP = new Player(0,0,this);
    vEntities.push_back(playerP);
    //Set the player texture to the first texture in the texture vector.
    vEntities.back()->spr.setTexture(*vTextures[0]);


    //Load the UI font from file.
    arialFont.loadFromFile("res//arial.ttf");

    //Set the character size, scale, font and string of the text part of UI
    hpText.setCharacterSize(60);
    hpText.setScale(0.5,0.5);
    hpText.setString("Health:");
    hpText.setFont(arialFont);


    //Set the width and color of the healthbar part of the UI.
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(80, 25));


}


void GameManager::init()
{

    //Randomly generate a map full of asteroids and some Enemies.
    for(int i = -20; i< 20; i+=3)
    {
        for(int j = -20; j < 20;j+=3)
        {
            vEntities.push_back(new Asteroid((i*rand()%1000)+200,(j*3*rand()%1000)+200,this));
        }
    }


    for(int i = -20; i< 20; i+=8)
    {
        for(int j = -20; j < 20;j+=8)
        {
            vEntities.push_back(new Enemy((i*rand()%1000)+200,(j*3*rand()%1000)+200,this));
        }
    }
}

void GameManager::tick()
{
    //Game loop
    while(win.isOpen())
    {

        sf::Event event;

        //Check for sfml window events. Technical requirement of SFML, without this, the application might crash.
        while (win.pollEvent(event))
        {
            //Check for event of sf::Event::Closed type, such as clicking on the "X" to close the window.
            if (event.type == sf::Event::Closed)
                win.close();
        }

        //Center the game camera on the player.
        view.setCenter(playerP->spr.getPosition().x, playerP->spr.getPosition().y);
        win.setView(view);

        //Re-set the position of the user interface to be in top left of the window.
        hpText.setPosition(view.getCenter().x - view.getSize().x/2, view.getCenter().y - view.getSize().y/2);
        hpBar.setPosition(hpText.getGlobalBounds().left, hpText.getGlobalBounds().top + hpText.getGlobalBounds().height);
        hpBar.setSize(sf::Vector2f(80.f*(playerP->health/100.f), 25.f));


        //If player lost all of their health, quit the game.
        if(playerP->health<=0)
            win.close();

        //Lock the game logic to a designated framerate.
        if(fpsClock.getElapsedTime().asMilliseconds() > 1000.f/FPS)
        {
            //Reset the FPS clock.
            fpsClock.restart();

            //Call all entities update functions.
            for(int i = vEntities.size()-1; i >= 0; i--)
            {
                vEntities[i]->update();
            }
            //Check if bullets are too far and delete them.
            for(int i = vBullets.size()-1; i >= 0; i--)
            {
                if(vBullets[i]->spr.getPosition().x - playerP->spr.getPosition().x > win.getDefaultView().getSize().x/2 ||
                   vBullets[i]->spr.getPosition().y - playerP->spr.getPosition().y > win.getDefaultView().getSize().y/2)
                {



                    for(int j = vEntities.size()-1; j>=0;j--)
                    {
                        if(vEntities[j] == vBullets[i])
                        {

                            vEntities.erase(vEntities.begin() + j);
                            break;
                        }
                    }

                    vBullets.erase(vBullets.begin()+i);
                }
            }


            //Call the collide method.
            collide();
            //Call the render method
            render();

        }



        //printf("entities size: %d", vEntities.size());
    }
}

void GameManager::collide()
{
    //Check collisions between all bullets with other entities.
    for(int j = vBullets.size()-1; j >=0; j--)
    {
        //With asteroids.
        for(int i = vAsteroids.size()-1; i >= 0; i--)
        {

            if(vAsteroids[i]->spr.getGlobalBounds().intersects(vBullets[j]->spr.getGlobalBounds()))
            {



                //Erase the asteroid from both entity vector and asteroid vector.
                //Erase the bullet from the entity vector and the bullet vector.
                for(int x = 0; x < vEntities.size(); x++)
                {
                    if(vEntities[x] == vAsteroids[i])
                        vEntities.erase(vEntities.begin() + x);
                    if(vEntities[x] == vBullets[j])
                        vEntities.erase(vEntities.begin() + x);
                }

                vAsteroids.erase(vAsteroids.begin() + i);
                vBullets.erase(vBullets.begin() + j);

            }
        }
        //With enemies
        for(int i = vEnemies.size()-1; i >= 0; i--)
        {
            //Do not kill the enemy if the bullet was fired by this particular enemy.
            if(vBullets[j]->firedBy == vEnemies[i])
                continue;
            if(vEnemies[i]->spr.getGlobalBounds().intersects(vBullets[j]->spr.getGlobalBounds()))
            {

                //Erase the enemy from both entity vector and enemy vector.
                //Erase the bullet from the entity vector and the bullet vector.
                for(int x = 0; x < vEntities.size(); x++)
                {
                    if(vEntities[x] == vEnemies[i])
                        vEntities.erase(vEntities.begin() + x);
                    if(vEntities[x] == vBullets[j])
                        vEntities.erase(vEntities.begin() + x);
                }
                vEnemies.erase(vEnemies.begin() + i);
                vBullets.erase(vBullets.begin() + j);

            }

        }

        //With the player
        if(playerP->spr.getGlobalBounds().intersects(vBullets[j]->spr.getGlobalBounds()) && vBullets[j]->firedBy != playerP)
        {

            //Erase the bullet from the entity vector and the bullet vector.
            for(int x = 0; x < vEntities.size(); x++)
            {
                if(vEntities[x] == vBullets[j])
                    vEntities.erase(vEntities.begin() + x);
            }
            vBullets.erase(vBullets.begin() + j);


            //Subtract 10 points from player's health.
            playerP->health-=10;

        }

    }
}

void GameManager::render()
{

    //Clear the game screen to Black.
    win.clear(sf::Color::Black);

    //Draw all entities.
    for(unsigned i = 0; i < vEntities.size(); i++)
    {
        win.draw(vEntities[i]->spr);
    }

    //Draw the user UI.
    win.draw(hpBar);
    win.draw(hpText);


    //Display all elements to the window.
    win.display();


}


GameManager::~GameManager()
{
    vBullets.clear();
    vEnemies.clear();
    vAsteroids.clear();
    delete playerP;

}
