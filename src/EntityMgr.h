#pragma once
#include "Entity381.h"
#include <memory>
#include <list>

class EntityMgr
{
public:
    std::map<const int, std::shared_ptr<Entity381>> entities;
    std::shared_ptr<Entity381> currentEntity;
    Entity381* CreateEntity(EntityType type, Ogre::Vector3 pos, float heading);
    void Tick(float dt);
};
