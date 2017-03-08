//============================================
// Name        : EntityMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "EntityMgr.h"
#include "Aspects.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#  include <OGRE/SdkTrays.h>
#  include <OGRE/SdkCameraMan.h>
#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>
#endif

std::shared_ptr<Entity381> EntityMgr::CreateEntity(std::string id, EntityType type, Ogre::Vector3 pos, float heading)
{
    // Create our Entity381
    std::shared_ptr<Entity381> entity = nullptr;
    switch (type)
    {
    case EntityType::ENTITY_ALIEN:
        entity = std::make_shared<Alien>(id);
        break;

    case EntityType::ENTITY_CARRIER:
        entity = std::make_shared<Carrier>(id);
        break;

    case EntityType::ENTITY_DESTROYER:
        entity = std::make_shared<Destroyer>(id);
        break;

    case EntityType::ENTITY_FRIGATE:
        entity = std::make_shared<Frigate>(id);
        break;

    case EntityType::ENTITY_SPEEDBOAT:
        entity = std::make_shared<Speedboat>(id);
        break;
    default:
        return nullptr;
    }
    entity->heading = entity->desiredHeading = heading;
    entity->position = pos;

    // Create the associated OGRE entity, mesh, etc
    const auto rotation = Ogre::Quaternion(Ogre::Radian(entity->heading), Ogre::Vector3::UNIT_Y);
    //std::shared_ptr<Ogre::Entity> ogreEntity(sceneMgr->createEntity(entity->meshName));
    //std::shared_ptr<Ogre::SceneNode> node(sceneMgr->getRootSceneNode()->createChildSceneNode(entity->position, rotation));
    Ogre::Entity* ogreEntity(sceneMgr->createEntity(entity->meshName));
    Ogre::SceneNode* ogreSceneNode(sceneMgr->getRootSceneNode()->createChildSceneNode(entity->position, rotation));
    ogreSceneNode->attachObject(ogreEntity);

    entity->ogreEntity = std::make_shared<Ogre::Entity>(*ogreEntity);
    entity->ogreSceneNode = std::make_shared<Ogre::SceneNode>(*ogreSceneNode);

    // Aspects
    auto physicsAspect = std::make_shared<PhysicsAspect>();
    auto renderableAspect = std::make_shared<RenderableAspect>();

    physicsAspect->parentEntity = entity;
    renderableAspect->parentEntity = entity;

    entity->aspects.emplace("PhysicsAspect", physicsAspect);
    entity->aspects.emplace("RenderableAspect", renderableAspect);

    entities.emplace(id, entity);
}

std::shared_ptr<Entity381> EntityMgr::GetEntity(std::string id)
{
    if (entities.size() < 1) return nullptr;
    auto pos = entities.find(id);
    if (pos == entities.end()) return nullptr;
    return pos->second;
}

void EntityMgr::Tick(float dt)
{
    for (std::pair<std::string, std::shared_ptr<Entity381>> entity : entities)
    {
        entity.second->Tick(dt);
    }
}
