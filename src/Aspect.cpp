/*
 * Aspect.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "Aspect.h"
#include "Utils.h"
#include "Entity381.h"

Aspect::Aspect (Entity381 * ent){
	this->entity = ent;

}

Aspect::~Aspect(){

}


Renderable::Renderable(Entity381 * ent): Aspect(ent){
	return;
}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
	entity->ogreSceneNode->setPosition(entity->pos);
	entity->ogreSceneNode->setOrientation(Ogre::Quaternion::IDENTITY);
	entity->ogreSceneNode->yaw(Ogre::Radian(-entity->heading));
	if (entity->isSelected)
		entity->ogreSceneNode->showBoundingBox(true);
	else
		entity->ogreSceneNode->showBoundingBox(false);
}

Physics::Physics(Entity381 * ent): Aspect(ent) {

}

Physics::~Physics(){

}

//static float FixAngle(float radiansAngle){
//
//	while (radiansAngle > Ogre::Math::TWO_PI)
//		radiansAngle -= Ogre::Math::TWO_PI;
//	while (radiansAngle < 0)
//		radiansAngle += Ogre::Math::TWO_PI;
//
//	return radiansAngle;
//}
static float RadToDegree = 57.2958; //180/pi

void Physics::Tick(float dt){

	if(entity->speed < entity->desiredSpeed)
		entity->speed += entity->acceleration *dt;
	if(entity->speed > entity->desiredSpeed)
		entity->speed -= entity->acceleration *dt;

	//entity->speed = std::max(entity->minSpeed, std::min(entity->speed, entity->maxSpeed)); //clamp

	if(entity->heading < entity->desiredHeading)
		entity->heading += entity->turnRate * dt;
	if(entity->heading > entity->desiredHeading)
		entity->heading -= entity->turnRate * dt;

	//entity->heading = FixAngle(entity->heading); // between -pi and pi

	//Ogre::Quaternion ori = Ogre::Quaternion(Ogre::Radian(entity->heading), Ogre::Vector3::NEGATIVE_UNIT_Y);
	//entity->heading = ori.getYaw();
	//std::cout << "Heading: " << entity->heading * RadToDegree << " DesiredHeading: " << entity->desiredHeading * RadToDegree << std::endl;
	//std::cout << "Speed  : " << entity->speed << " DesiredSpeed:   " << entity->desiredSpeed << std::endl;
	//std::cout << "cos: " << cos(entity->heading) << " sin: " << sin(entity->desiredHeading) << std::endl;
	
	entity->vel = Ogre::Vector3(cos(entity->heading) * entity->speed, 0, sin(entity->heading) * entity->speed);
	entity->pos += entity->vel * dt;

}
