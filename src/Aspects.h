//============================================
// Name        : Aspects.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once
#include "Entity381.h"

class PhysicsAspect : public Aspect
{
public:
    void Tick(float dt) override;
};

class RenderableAspect : public Aspect
{
public:
    void Tick(float dt) override;
};

