//============================================
// Name        : Aspects.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once
#include "Entity381.h"

class PhysicsAspect : Aspect
{
public:
    void Tick(float dt) override;
};

class RenderableAspect : Aspect
{
public:
    void Tick(float dt) override;
};

