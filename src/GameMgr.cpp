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
    int offset = -400;
    auto CreateEntity = [this, &offset](EntityType type) -> Entity381*
    {
        auto entity = engine->entityMgr->CreateEntity(type, Ogre::Vector3(offset, 0, 0), 1.5); 
        std::cout << "Created: " << entity->meshfile << std::endl;
        offset += 200;
        return entity;
    };

    CreateEntity(EntityType::ALIEN)->isSelected = true;
    CreateEntity(EntityType::CIGARETTE);
    CreateEntity(EntityType::CVN);
    CreateEntity(EntityType::FRIGATE);
    CreateEntity(EntityType::DDG);

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