//============================================
// Name        : Aspect.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once

#include "Entity381.h"

class Aspect
{

public:
	Aspect(Entity381* ent);
	virtual ~Aspect();

	virtual void Tick(float dt) = 0;
	Entity381 *entity;
};

class Renderable : public Aspect {
public:
	Renderable(Entity381* ent);
	~Renderable();
	virtual void Tick(float dt);
};


class Physics : public Aspect {
public:
	Physics(Entity381* ent);
	~Physics();
	virtual void Tick(float dt);
};