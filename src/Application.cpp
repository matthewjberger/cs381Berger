//============================================
// Name        : Application.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
// Description : Assignment 1                 
//============================================

#include "Application.h"

Application::Application(void)
{
    deltaVelocity = 50.0f;
    yaw = 0.0f;
    position = Ogre::Vector3::ZERO;
    velocity = Ogre::Vector3::ZERO;
    keyTime = 0.01f;
    keyboardTimer = keyTime;
    cubeSceneNode = 0;
}

Application::~Application(void)
{
}

void Application::createScene(void)
{
    // Create the entity manager
    entityMgr = std::make_shared<EntityMgr>();

    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    mCamera->lookAt(Ogre::Vector3(0, 0, 0));

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0, 80.0, 50.0);

    // a fixed point in the ocean so you can see relative motion

    Ogre::Entity* ogreEntityFixed = mSceneMgr->createEntity("ogre.mesh");
    Ogre::SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
    sceneNode->attachObject(ogreEntityFixed);
    sceneNode->showBoundingBox(true);

    // A node to attach the camera to so we can move the camera node instead of the camera.
    cameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    cameraNode->setPosition(0, 200, 500);
    cameraNode->attachObject(mCamera);

    MakeGround();
    MakeSky();

}

void Application::UpdateCamera(const Ogre::FrameEvent& fe)
{
    float move = 400.0f;
    float rotate = 0.1f;

    Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_W))
        dirVec.z -= move;

    if (mKeyboard->isKeyDown(OIS::KC_S))
        dirVec.z += move;

    if (mKeyboard->isKeyDown(OIS::KC_E))
        dirVec.y += move;

    if (mKeyboard->isKeyDown(OIS::KC_F))
        dirVec.y -= move;

    if (mKeyboard->isKeyDown(OIS::KC_A))
    {
        if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            cameraNode->yaw(Ogre::Degree(5 * rotate));
        else
            dirVec.x -= move;
    }

    if (mKeyboard->isKeyDown(OIS::KC_D))
    {
        if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            cameraNode->yaw(Ogre::Degree(-5 * rotate));
        else
            dirVec.x += move;
    }

    cameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& fe) 
{
    mKeyboard->capture();
    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) 
    {
        return false;
    }

    mTrayMgr->frameRenderingQueued(fe);

    UpdateCamera(fe);
    UpdateEntityMgr(fe);
    entityMgr->Tick(fe.timeSinceLastFrame);
    return true;
}

void Application::UpdateEntityMgr(const Ogre::FrameEvent& fe) 
{
    keyboardTimer -= fe.timeSinceLastEvent;

    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)) {
        keyboardTimer = keyTime;
        velocity.z -= deltaVelocity;
    }
    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) {
        keyboardTimer = keyTime;
        velocity.z += deltaVelocity;
    }
    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)) {
        keyboardTimer = keyTime;
        velocity.x -= deltaVelocity;
    }
    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)) {
        keyboardTimer = keyTime;
        velocity.x += deltaVelocity;
    }
    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD9)) {
        keyboardTimer = keyTime;
        velocity.y += deltaVelocity;
    }
    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD3)) {
        keyboardTimer = keyTime;
        velocity.y -= deltaVelocity;
    }

    if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)) {
        keyboardTimer = keyTime;
        velocity = Ogre::Vector3::ZERO;
    }

}

void Application::MakeGround()
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

    Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
    groundEntity->setMaterialName("OceanHLSL_GLSL");
    //groundEntity->setMaterialName("Ocean2_Cg");
    //groundEntity->setMaterialName("NavyCg");

}

void Application::MakeSky() 
{

    mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void Application::MakeFog()
{
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);
    mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}
