//============================================
// Name        : Engine.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "engine.h"
#include <OgreTimer.h>

Engine::Engine() {
	gfxMgr = 0;
	inputMgr = 0;
	entityMgr = 0;
	gameMgr = 0;
	keepRunning = true;

}

Engine::~Engine() {

}

void Engine::stop() {
	keepRunning = false;
}

void Engine::init() {
	// construct
	gfxMgr = new GfxMgr(this);
	std::cout << "Constructed GfxMgr" << std::endl;
	inputMgr = new InputMgr(this);
	entityMgr = new EntityMgr(this);
	gameMgr = new GameMgr(this);
	// initialize
	gfxMgr->init();
	inputMgr->initialize(gfxMgr->mWindow, gfxMgr->mRoot);
	entityMgr->init();
	gameMgr->init();
	// load level to play
	gfxMgr->load_level();
	inputMgr->load_level();
	entityMgr->load_level();
	gameMgr->load_level();
}

void Engine::tickAll(float dt) {
	gfxMgr->tick(dt);
	inputMgr->tick(dt);
	entityMgr->tick(dt);
	gameMgr->tick(dt);
	if (inputMgr->receivedAbort)
		keepRunning = false;
}

void Engine::shutdown() {
	inputMgr->stop();
	gfxMgr->stop();
	entityMgr->stop();
	gameMgr->stop();
}
void Engine::run() {
	Ogre::Timer* timer = new Ogre::Timer();
	float oldTime = timer->getMilliseconds() / 1000.0f;
	float newTime;
	float dt = 0.001f;
	while (keepRunning) {
		newTime = timer->getMilliseconds() / 1000.0f;
		dt = newTime - oldTime;
		oldTime = newTime;
		tickAll(dt);
	}
	shutdown();

	return;
}