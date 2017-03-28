//============================================
// Name        : GameMgr.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once

#include "mgr.h"

class GameMgr : public Mgr
{
public:

    GameMgr(Engine *eng) : Mgr(eng) {}

    void tick(float dt);
    void init();
    void load_level();
    void stop();
};