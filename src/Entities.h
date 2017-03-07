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
    Destroyer(int id);
};

class Carrier : public Entity381
{
public:
    Carrier(int id);
};

class Speedboat : public Entity381
{
public:
    Speedboat(int id);
};


class Frigate : public Entity381
{
public:
    Frigate(int id);
};


class Alien : public Entity381
{
public:
    Alien(int id);
};
