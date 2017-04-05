#include "Command.h"

/* Move Command */

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location) : Command(ent, COMMAND_TYPE::COMMAND_MOVE_TO)
{
}

MoveTo::~MoveTo()
{
}

void MoveTo::init()
{
}

void MoveTo::tick(float dt)
{
}

bool MoveTo::done()
{
    return false;
}

/* Follow Command */

Follow::Follow(Entity381* ent) : Command(ent, COMMAND_TYPE::COMMAND_FOLLOW)
{
}

Follow::~Follow()
{
}

void Follow::init()
{
}

void Follow::tick(float dt)
{
}

bool Follow::done()
{
    return false;
}
