//============================================
// Name        : EntityMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "EntityMgr.h"
#include "Aspects.h"

#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreConfigFile.h>

Entity381* EntityMgr::CreateEntity(std::string id, EntityType type, Ogre::Vector3 pos, float heading)
{
    // Create our Entity381
    Entity381* entity = nullptr;
    switch (type)
    {
    case EntityType::ENTITY_ALIEN:
        entity = new Alien(id);
        break;

    case EntityType::ENTITY_CARRIER:
        entity = new Carrier(id);
        break;

    case EntityType::ENTITY_DESTROYER:
        entity = new Destroyer(id);
        break;

    case EntityType::ENTITY_FRIGATE:
        entity = new Frigate(id);
        break;

    case EntityType::ENTITY_SPEEDBOAT:
        entity = new Speedboat(id);
        break;
    default:
        return nullptr;
    }
    entity->heading = entity->desiredHeading = heading;
    entity->position = pos;

    // Create the associated OGRE entity, mesh, etc
    const auto rotation = Ogre::Quaternion(Ogre::Radian(entity->heading), Ogre::Vector3::UNIT_Y);
    auto ogreEntity(sceneMgr->createEntity(entity->meshName));
    auto ogreSceneNode(sceneMgr->getRootSceneNode()->createChildSceneNode(entity->position, rotation));
    ogreSceneNode->attachObject(ogreEntity);

    entity->ogreEntity = ogreEntity;
    entity->ogreSceneNode = ogreSceneNode;

    // Aspects
    auto physicsAspect = new PhysicsAspect();
    auto renderableAspect = new RenderableAspect();

    physicsAspect->parentEntity = entity;
    renderableAspect->parentEntity = entity;

    entity->aspects.emplace("PhysicsAspect", physicsAspect);
    entity->aspects.emplace("RenderableAspect", renderableAspect);

    entities.emplace(id, entity);
}

Entity381* EntityMgr::GetEntity(std::string id)
{
    if (entities.size() < 1) return nullptr;
    auto pos = entities.find(id);
    if (pos == entities.end()) return nullptr;
    return pos->second;
}

void EntityMgr::Tick(float dt)
{
    for (std::pair<std::string, Entity381*> entity : entities)
    {
        entity.second->Tick(dt);
    }
}
