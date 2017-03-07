#pragma once

#include "Entity381.h"

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
