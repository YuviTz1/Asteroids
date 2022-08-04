#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "playerSpaceship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"

class gameManager
{
private:
    std::vector<bullet> bulletVector;
    std::vector<asteroid> asteroidVector;

    int numAsteroids = 10;

public:
    playerSpaceship player;

    int score = 0;
    gameManager();
    void addBullet(playerSpaceship player);
    void checkBounds();
    void checkCollision();
    void update();
    void newAsteroids();

    void reset();
};