#include "Aspects.h"

void PhysicsAspect::Tick(float dt)
{
    // Update speed
    if(parentEntity->desiredSpeed < parentEntity->speed)
    {
        parentEntity->speed += parentEntity->acceleration;
    }

    // Update heading
    if(parentEntity->heading < parentEntity->desiredHeading)
    {
    }

    parentEntity->velocity = Ogre::Vector3(parentEntity->speed * cos(parentEntity->heading),
        0.0f, -1 * parentEntity->speed * sin(parentEntity->heading));
}

void RenderableAspect::Tick(float dt)
{
    parentEntity->rotation = Ogre::Quaternion(Ogre::Radian(parentEntity->heading), Ogre::Vector3::UNIT_Y);
    parentEntity->ogreSceneNode->setPosition(parentEntity->position);
}
