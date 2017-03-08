//============================================
// Name        : Entities.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once

#include "Entity381.h"

enum EntityType
{
    ENTITY_DESTROYER,
    ENTITY_CARRIER,
    ENTITY_SPEEDBOAT,
    ENTITY_FRIGATE,
    ENTITY_ALIEN
};

class Destroyer : public Entity381
{
public:
    Destroyer(std::string id);
};

class Carrier : public Entity381
{
public:
    Carrier(std::string id);
};

class Speedboat : public Entity381
{
public:
    Speedboat(std::string id);
};


class Frigate : public Entity381
{
public:
    Frigate(std::string id);
};


class Alien : public Entity381
{
public:
    Alien(std::string id);
};
