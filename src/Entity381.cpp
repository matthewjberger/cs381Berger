/*
 * Entity381.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "Entity381.h"
#include "Aspect.h"

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
	this->aspects.push_front(r);
	this->aspects.push_front(p);

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

Ddg::Ddg(Ogre::Vector3 pos, float heading) : Entity381(EntityType::DDG, pos, heading){
	this->meshfile = "ddg51.mesh";
	this->acceleration = 1.0f;
	this->turnRate = 0.1f;
}

Ddg::~Ddg(){

}

Cigarette::Cigarette(Ogre::Vector3 pos, float heading) : Entity381(EntityType::CIGARETTE, pos, heading){
	this->meshfile = "cigarette.mesh";
	this->acceleration = 1.5f;
	this->turnRate = 0.3f;
}

Cigarette::~Cigarette(){

}

Alien::Alien(Ogre::Vector3 pos, float heading) : Entity381(EntityType::ALIEN, pos, heading){
	this->meshfile = "alienship.mesh";
	this->turnRate = 0.5f;
	this->acceleration = 1.8f;
}

Alien::~Alien(){

}

Cvn::Cvn(Ogre::Vector3 pos, float heading) : Entity381(EntityType::CVN, pos, heading){
	this->meshfile = "cvn68.mesh";
	this->turnRate = 0.05f;
	this->acceleration = 0.75f;
}

Cvn::~Cvn(){

}

Frigate::Frigate(Ogre::Vector3 pos, float heading) : Entity381(EntityType::FRIGATE, pos, heading){
	this->meshfile = "sleek.mesh";
	this->turnRate = 0.15f;
	this->acceleration = 1.1f;
}

Frigate::~Frigate(){

}






