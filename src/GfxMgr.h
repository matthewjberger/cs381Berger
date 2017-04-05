/*
 * GxfMgr.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include "mgr.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <SdkTrays.h>

class GfxMgr : public Mgr {

private:
	//Ogre variables
	Ogre::Camera* ogreCamera;
	Ogre::String resources;
	Ogre::String plugins;
	Ogre::ConfigFile cf;
	void loadConfig(Ogre::ConfigFile cf);
	void configureRenderSystem();
	void initResources();

	void createSceneManager();
	void createCamera();
	Ogre::Viewport *ogreViewport;
	void createViewport();

    // Ray Casting
    Ogre::RaySceneQuery* raySceneQuery;

public:

	GfxMgr(Engine *eng);
	~GfxMgr();

	virtual void tick(float dt);
	virtual void init();
	virtual void loadLevel();
	virtual void stop();

	Ogre::Root *ogreRoot;
	Ogre::RenderWindow* ogreRenderWindow;
	Ogre::SceneManager* ogreSceneManager;
	Ogre::SceneNode *cameraNode, *pitchNode;
    Ogre::OverlaySystem* overlaySystem;

	void testScene();
    Ogre::RaySceneQueryResult* PerformRaycastFromCursorNearest(OgreBites::SdkTrayManager*);
};



#endif /* GFXMGR_H_ */
