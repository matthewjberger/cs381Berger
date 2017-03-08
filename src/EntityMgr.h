//============================================
// Name        : EntityMgr.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once
#include "Entity381.h"
#include "Entities.h"
#include <OgreSceneManager.h>
#include <memory>

class EntityMgr
{
public:
    explicit EntityMgr(Ogre::SceneManager* sceneMgr_)
        : currentEntity(nullptr), sceneMgr(sceneMgr_) {}
    std::map<const std::string, Entity381*> entities;
    Entity381* currentEntity;
    Entity381* CreateEntity(std::string id, EntityType type, Ogre::Vector3 pos, float heading);
    Entity381* GetEntity(std::string id);
    void Tick(float dt);
private:
    Ogre::SceneManager* sceneMgr;
};
