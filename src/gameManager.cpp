#include "gameManager.hpp"

gameManager::gameManager()
{
    newAsteroids();
}

void gameManager::newAsteroids()
{
    // spawn new asteroids
    for (int i = 0; i < numAsteroids; i++)
    {
        asteroidVector.push_back(asteroid());
    }
    numAsteroids += 2;
}

void gameManager::addBullet(playerSpaceship player)
{
    bulletVector.push_back(bullet(player));
}

void gameManager::checkBounds()
{
    if (bulletVector.size() != 0)
    {
        // remove bullets from vector when they go offscreen
        auto i = std::remove_if(bulletVector.begin(), bulletVector.end(), [&](bullet b)
                                {
                                    //check bounds and place all offscreen bullets at the end of the vector
            if(b.x.x>2||b.x.x<-2)
            {
                return true;
            }
            if(b.x.y>2||b.x.y<-2)
            {
                return true;
            }
            return false; });

        if (i != bulletVector.end())
        {
            bulletVector.erase(i);
        }
    }

    if (asteroidVector.size() != 0)
    {
        // remove asteroids from vector when they are destroyed
        auto i = std::remove_if(asteroidVector.begin(), asteroidVector.end(), [&](asteroid a)
                                { return a.destroy; });

        if (i != asteroidVector.end())
        {
            asteroidVector.erase(i);
        }
    }
}

void gameManager::update()
{
    // update bullet positions and draw each bullet
    for (std::vector<bullet>::iterator it = bulletVector.begin(); it != bulletVector.end(); it++)
    {
        it->update();
        it->draw();
    }

    // update asteroid positions and draw each asteroid
    for (std::vector<asteroid>::iterator it = asteroidVector.begin(); it != asteroidVector.end(); it++)
    {
        it->update();
        it->draw();
    }

    player.update();
    player.draw();

    // if all asteroids are destroyed, spawn new ones
    if (asteroidVector.size() == 0)
    {
        newAsteroids();
    }
}

void gameManager::checkCollision()
{
    for (std::vector<asteroid>::iterator asteroidsVectorIterator = asteroidVector.begin(); asteroidsVectorIterator != asteroidVector.end(); asteroidsVectorIterator++)
    {
        for (std::vector<bullet>::iterator bulletVectorIterator = bulletVector.begin(); bulletVectorIterator != bulletVector.end(); bulletVectorIterator++)
        {
            // check collisions between each bullet and asteroid
            // by assuming asteroid as circle and checking its distance from bullet
            if (pow((asteroidsVectorIterator->x.x - bulletVectorIterator->x.x), 2) + pow((asteroidsVectorIterator->x.y - bulletVectorIterator->x.y), 2) <= asteroidsVectorIterator->radius)
            {

                asteroidsVectorIterator->destroy = true;
                bulletVectorIterator->x.x = 100; // make bullet go offscreen so that
                                                 // checkBounds function can remove it
                score += 1000;
            }
        }

        // if collision between player and asteroid, reset the game
        if (pow((asteroidsVectorIterator->x.x - player.x.x), 2) + pow((asteroidsVectorIterator->x.y - player.x.y), 2) <= asteroidsVectorIterator->radius)
        {
            reset();
        }
    }
}

void gameManager::reset()
{
    std::cout << "Score: " << score << std::endl;
    score = 0;
    asteroidVector.clear();
    bulletVector.clear();
    player.reset();

    numAsteroids = 10;
    newAsteroids();
}