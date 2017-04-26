/*
 * Entity.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#ifndef ENTITY381_H_
#define ENTITY381_H_

#include <OgreVector3.h>
#include <OgreSceneNode.h>

#include "Types.h"


#include <list>

class Aspect;

class Entity381 {

private:
	//
	static unsigned int nextId;

protected:
	//

public:

	Entity381(EntityType entityType, Ogre::Vector3 pos, float heading);
	~Entity381();
	void Tick(float dt);
	void DefaultInit();

	//static stuff
	float maxSpeed, minSpeed;
	float acceleration, turnRate;
	EntityType entityType;
	std::string meshfile;

	//Ogre stuff
	Ogre::Vector3 pos;
	Ogre::Vector3 vel;
	Ogre::SceneNode *ogreSceneNode;
	Ogre::Entity* ogreEntity;

	//Engine stuff dynamic
	float speed, heading;
	float desiredSpeed, desiredHeading;

	//selection
	bool isSelected;

	unsigned int entityId;

	std::list<Aspect*> aspects;
};

class PlayerShip: public Entity381 {

public:
	PlayerShip(Ogre::Vector3 pos, float heading);
	~PlayerShip();

};

class EnemyShip: public Entity381 {

public:
	EnemyShip(Ogre::Vector3 pos, float heading);
	~EnemyShip();
};

#endif /* ENTITY381_H_ */
