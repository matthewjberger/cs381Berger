//============================================
// Name        : EntityMgr.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once
#include "Entity381.h"
#include "Entities.h"
#include <memory>

class EntityMgr
{
public:
    explicit EntityMgr(Ogre::SceneManager* sceneMgr_) : sceneMgr(sceneMgr_){}
    std::map<std::string, std::shared_ptr<Entity381>> entities;
    std::shared_ptr<Entity381> currentEntity;
    std::shared_ptr<Entity381> CreateEntity(std::string name, EntityType type, Ogre::Vector3 pos, float heading);
    std::shared_ptr<Entity381> GetEntity(std::string id);
    void Tick(float dt);
private:
    Ogre::SceneManager* sceneMgr;
};
