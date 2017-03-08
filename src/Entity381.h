//============================================
// Name        : Entity381.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once
#include <OgreVector3.h>
#include <OgreSceneNode.h>

class Aspect;

class Entity381
{
public:
    Entity381();

    void Tick(float dt);

    std::map<const std::string, std::shared_ptr<Aspect>> aspects;
    std::string entityId;
    std::string entityName;
    float minSpeed, maxSpeed;
    float speed, desiredSpeed;
    float heading, desiredHeading;
    float acceleration;
    float turningRate;
    std::string meshName;
    Ogre::Vector3 position;
    Ogre::Vector3 velocity;
    std::shared_ptr<Ogre::SceneNode> ogreSceneNode;
    std::shared_ptr<Ogre::Entity> ogreEntity;
    Ogre::Quaternion rotation;
};

class Aspect
{
public:
    virtual ~Aspect(){}
    virtual void Tick(float dt){}
    std::shared_ptr<Entity381> parentEntity;
};
