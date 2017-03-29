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

    void tick(float dt) override;
    void init() override;
    void loadLevel() override;
    void stop() override;
};