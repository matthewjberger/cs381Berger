//============================================
// Name        : Aspects.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "Aspects.h"

void PhysicsAspect::Tick(float dt)
{
    // Update speed
    if(parentEntity->speed < parentEntity->desiredSpeed)
    {
        parentEntity->speed += parentEntity->acceleration;
    }
    else if(parentEntity->speed > parentEntity->desiredSpeed)
    {
        parentEntity->speed -= (2 * parentEntity->acceleration);
    }

    // Update heading
    if(parentEntity->heading < parentEntity->desiredHeading)
    {
        if((parentEntity->desiredHeading - parentEntity->heading) < parentEntity->turningRate)
        {
            parentEntity->heading = parentEntity->desiredHeading;
        }
        else
        {
            parentEntity->heading += parentEntity->turningRate;
        }
    }
    else if(parentEntity->heading > parentEntity->desiredHeading)
    {
        if((parentEntity->heading - parentEntity->desiredHeading) < parentEntity->turningRate)
        {
            parentEntity->heading = parentEntity->desiredHeading;
        }
        else
        {
            parentEntity->heading -= parentEntity->turningRate;
        }
    }

    // Update velocity
    parentEntity->velocity = Ogre::Vector3(
        parentEntity->speed * cos(parentEntity->heading),
        0.0f, -1 * parentEntity->speed * sin(parentEntity->heading));
    
    // Update position. 
    parentEntity->position = parentEntity->position + (parentEntity->velocity * dt);
}

void RenderableAspect::Tick(float dt)
{
    // Update the scene node
    parentEntity->rotation = Ogre::Quaternion(Ogre::Radian(parentEntity->heading), Ogre::Vector3::UNIT_Y);
    parentEntity->ogreSceneNode->setPosition(parentEntity->position);
    parentEntity->ogreSceneNode->setOrientation(parentEntity->rotation);
}
