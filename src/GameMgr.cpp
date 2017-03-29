//============================================
// Name        : GameMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "gameMgr.h"
#include "Types.h"
#include "Engine.h"
#include <OgreVector3.h>

void GameMgr::tick(float dt)
{

}

void GameMgr::init()
{
    /* Scene */

    // Light
    engine->gfxMgr->ogreSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    Ogre::Light* light = engine->gfxMgr->ogreSceneMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);

    // Entities
    engine->entityMgr->CreateEntity(EntityType::ALIEN, Ogre::Vector3(-200, 0, 0), 1.5);
    engine->entityMgr->CreateEntity(EntityType::CIGARETTE, Ogre::Vector3(100, 0, 0), 1.5);
    engine->entityMgr->CreateEntity(EntityType::CVN, Ogre::Vector3(400, 0, 0), 1.5);
    engine->entityMgr->CreateEntity(EntityType::FRIGATE, Ogre::Vector3(600, 0, 0), 1.5);
    engine->entityMgr->selectedEntity = engine->entityMgr->CreateEntity(EntityType::DDG, Ogre::Vector3(800, 0, 0), 1.5);

    // Environment
    engine->gfxMgr->MakeGround();
    engine->gfxMgr->MakeSky();
}

void GameMgr::loadLevel()
{

}

void GameMgr::stop()
{

}