//============================================
// Name        : Entities.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "Entities.h"

Destroyer::Destroyer(std::string id)
{
    entityId = id;
    entityName = "Destroyer";
    meshName = "ddg51.mesh";
    maxSpeed = 100;
    acceleration = 0.75;
}

Carrier::Carrier(std::string id)
{
    entityId = id;
    entityName = "Carrier";
    meshName = "cvn68.mesh";
    maxSpeed = 160;
    acceleration = 0.45;
    turningRate = 0.00075;
}

Speedboat::Speedboat(std::string id)
{
    entityId = id;
    entityName = "Speedboat";
    meshName = "cigarette.mesh";
    maxSpeed = 140;
    acceleration = 0.3;
    turningRate = 0.005;
}

Frigate::Frigate(std::string id)
{
    entityId = id;
    entityName = "Frigate";
    meshName = "sleek.mesh";
    maxSpeed = 120;
    acceleration = 0.2;
    turningRate = 0.04;
}

Alien::Alien(std::string id)
{
    entityId = id;
    entityName = "Alien";
    meshName = "alienship.mesh";
    maxSpeed = 200;
    acceleration = 0.175;
    turningRate = 0.01;
}
