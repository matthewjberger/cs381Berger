//============================================
// Name        : GfxMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "GfxMgr.h"
#include "Engine.h"

void GfxMgr::tick(float dt)
{
    mRoot->renderOneFrame();
}

void GfxMgr::InitResources()
{
    mResourcesCfg = Ogre::StringUtil::BLANK;
    mPluginsCfg = Ogre::StringUtil::BLANK;
    ogreSceneMgr = nullptr;
    mCamera = nullptr;
    mCameraNode = nullptr;

#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    mRoot = new Ogre::Root(mPluginsCfg);
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
        return;

    mWindow = mRoot->initialise(true, "CS381 - Assignment 3");
    mWindow->setFullscreen(false, 800, 600);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    ogreSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

void GfxMgr::init()
{
    InitResources();

    // Create a camera and attach it to a scene node
    mCamera = ogreSceneMgr->createCamera("MainCam");
    mCamera->setPosition(0, 200, 500);
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mCameraNode = ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
    mCameraNode->setPosition(0, 200, 500);
    mCameraNode->attachObject(mCamera);

    // viewport
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) /
        Ogre::Real(vp->getActualHeight()));
}

void GfxMgr::stop()
{
    if (mRoot) delete mRoot;
}

void GfxMgr::MakeGround() const
{
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane(
        "ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        15000, 15000, 20, 20,
        true,
        1, 5, 5,
        Ogre::Vector3::UNIT_Z);

    Ogre::Entity* groundEntity = ogreSceneMgr->createEntity("ground");
    ogreSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
    //groundEntity->setMaterialName("OceanHLSL_GLSL");
    //groundEntity->setMaterialName("Ocean2_Cg");
    //groundEntity->setMaterialName("NavyCg");}
}

void GfxMgr::MakeSky() const
{
    ogreSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
}

void GfxMgr::MakeFog() const
{
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);
    this->ogreSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}
