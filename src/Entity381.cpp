/*
 * Entity381.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "Entity381.h"
#include "Aspect.h"
#include "UnitAI.h"

unsigned int Entity381::nextId = 0;

Entity381::Entity381(EntityType entType, Ogre::Vector3 pos, float heading){
	entityType = entType;
	this->pos = pos;
	this->heading = heading;
	this->vel = Ogre::Vector3::ZERO;
	this->speed = 0;

	this->isSelected = false;

	this->aspects.clear();
	Renderable *r = new Renderable(this);
	Physics *p = new Physics(this);
    UnitAI *ai = new UnitAI(this);
	this->aspects.push_front(r);
	this->aspects.push_front(p);
	this->aspects.push_front(ai);

	this->entityId = Entity381::nextId++;

	DefaultInit();
}

Entity381::~Entity381(){

}

void Entity381::DefaultInit(){
	this->acceleration = 0.5f;
	this->turnRate = 0.2f;

	this->maxSpeed = 100;
	this->minSpeed = 0;

	this->desiredHeading = 0;
	this->desiredSpeed = 0;

	this->meshfile = "cube.mesh";

}

void Entity381::Tick(float dt){
	for(std::list<Aspect*>::const_iterator ai = aspects.begin(); ai != aspects.end(); ++ai){
		(*ai)->Tick(dt);
	}
}

PlayerShip::PlayerShip(Ogre::Vector3 pos, float heading) : Entity381(EntityType::PLAYER, pos, heading){
	this->meshfile = "robot.mesh";
	this->acceleration = 1.0f;
	this->turnRate = 0.1f;
}

PlayerShip::~PlayerShip() {
}

EnemyShip::EnemyShip(Ogre::Vector3 pos, float heading) : Entity381(EntityType::ENEMY, pos, heading){
	this->meshfile = "ninja.mesh";
	this->acceleration = 1.0f;
	this->turnRate = 0.1f;
}

EnemyShip::~EnemyShip() {
}
