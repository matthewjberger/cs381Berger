//============================================
// Name        : GfxMgr.h 
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#pragma once

#include "mgr.h"
#include "GlobalIncludes.h"

class Engine;
class OgreGraphics;

class GfxMgr : public Mgr
{
public:

    GfxMgr(Engine *eng) : Mgr(eng) {}
    ~GfxMgr(){}

    void tick(float dt) override;
    void init() override;
    void loadLevel() override {};
    void stop() override;

    Ogre::Root* mRoot;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::SceneManager* ogreSceneMgr;
    Ogre::Camera* mCamera;
    Ogre::SceneNode* mCameraNode;

    void MakeGround();
    void MakeSky();
    void MakeFog();

private:
    void InitResources();
};
