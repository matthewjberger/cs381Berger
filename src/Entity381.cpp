//============================================
// Name        : Entity381.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "Entity381.h"

Entity381::Entity381()
{
    entityId = "default";
    minSpeed = 0.0f;
    maxSpeed = 0.0f;
    speed = 0.0f;
    desiredSpeed = 0.0f;
    heading = 0.0f;
    desiredHeading = 0.0f;
    acceleration = 0.0f;
    turningRate = 0.0f;
    meshName = "ogre.mesh";
    position = Ogre::Vector3::ZERO;
    velocity = Ogre::Vector3::ZERO;
    ogreSceneNode = nullptr;
    ogreEntity = nullptr;
    rotation = Ogre::Quaternion::IDENTITY;
}

void Entity381::Tick(float dt)
{
    for (std::pair<std::string, std::shared_ptr<Aspect>> aspect : aspects)
    {
        aspect.second->Tick(dt);
    }
}
