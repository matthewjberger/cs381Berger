/*
* Command.h
*
*  Created on: Mar 28, 2017
*      Author: sushil
*/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <OgreVector3.h>

class Entity381;

enum COMMAND_TYPE
{
    COMMAND_MOVE_TO,
    COMMAND_FOLLOW,
};

class Command {

public:
    Command(Entity381* ent, COMMAND_TYPE ct)
    : entity(ent), commandType(ct){}
    virtual ~Command(){}

    virtual void init() = 0;
    virtual void tick(float dt) = 0;
    virtual bool done() = 0;

    Entity381* entity;
    COMMAND_TYPE commandType;

};

class MoveTo : public Command {

public:
    MoveTo(Entity381* ent, Ogre::Vector3 location);
    ~MoveTo();

    void init() override;
    void tick(float dt) override;
    bool done() override;

    Ogre::Vector3 targetLocation;
    float MOVE_DISTANCE_THRESHOLD;

};

class Follow : public Command {
public:
    Follow(Entity381* ent);
    ~Follow();
    
    void init() override;
    void tick(float dt) override;
    bool done() override;

    Entity381* targetEnt;
};




#endif /* COMMAND_H_ */