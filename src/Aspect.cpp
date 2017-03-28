//============================================
// Name        : Aspect.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "Aspect.h"

Aspect::Aspect(Entity381 * ent)
{
	this->entity = ent;
}

Aspect::~Aspect()
{
}


Renderable::Renderable(Entity381 * ent) : Aspect(ent)
{
	return;
}

Renderable::~Renderable()
{
}

void Renderable::Tick(float dt)
{
}

Physics::Physics(Entity381 * ent) : Aspect(ent)
{
}

Physics::~Physics()
{
}

void Physics::Tick(float dt)
{
}