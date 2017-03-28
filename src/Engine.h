//============================================
// Name        : Engine.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once

#include "GfxMgr.h"
#include "inputMgr.h"
#include "EntityMgr.h"
#include "gameMgr.h"

class Engine {
public:
	Engine();
	~Engine();


	EntityMgr*      entityMgr;
	GfxMgr*         gfxMgr;
	InputMgr*       inputMgr;
	GameMgr*        gameMgr;
	//SelectionMgr* selectionMgr;
	//ControlMgr*   controlMgr;

	void init();
	void run();
	void tickAll(float dt);
	void stop();
	void shutdown();

	bool keepRunning;
};
