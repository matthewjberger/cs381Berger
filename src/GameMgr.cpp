/*
 * gameMgr.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#include "gameMgr.h"
#include "engine.h"
#include <OgreMeshManager.h>

GameMgr::GameMgr(Engine *engine): Mgr(engine){

}

GameMgr::~GameMgr(){

}

void GameMgr::init(){

}

void GameMgr::loadLevel(){
//We know graphicsMgr is ready and initialized
	engine->gfxMgr->ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = engine->gfxMgr->ogreSceneManager->createLight("MainLight");
	light->setPosition(20.0, 80.0, 50.0);

	createEnts();
	createSky();
	createGround();
}

void GameMgr::stop(){

}

void GameMgr::tick(float dt){

}

void GameMgr::createEnts(){
	Entity381 * ent;
	int x = 0;
	ent = engine->entityMgr->CreateEntity(EntityType::DDG, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x+200;
	ent = engine->entityMgr->CreateEntity(EntityType::CIGARETTE, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x+200;
	ent = engine->entityMgr->CreateEntity(EntityType::ALIEN, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x+200;
	ent = engine->entityMgr->CreateEntity(EntityType::CVN, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x+300;
	ent = engine->entityMgr->CreateEntity(EntityType::FRIGATE, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;


	ent->isSelected = true;

}

void GameMgr::createGround(){

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  Ogre::MeshManager::getSingleton().createPlane(
	    "ground",
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    plane,
	    15000, 15000, 20, 20,
	    true,
	    1, 5, 5,
	    Ogre::Vector3::UNIT_Z);

	  Ogre::Entity* groundEntity = engine->gfxMgr->ogreSceneManager->createEntity("ground");
	  engine->gfxMgr->ogreSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
	  //groundEntity->setMaterialName("Ocean2_Cg");
	  //groundEntity->setMaterialName("NavyCg");

}

void GameMgr::createSky(){

	engine->gfxMgr->ogreSceneManager->setSkyBox(true, "Examples/MorningSkyBox");

}





