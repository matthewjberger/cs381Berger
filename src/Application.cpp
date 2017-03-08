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
    cycleTime = 0.30;
    cycleTimer = cycleTime;
    cubeSceneNode = nullptr;
}

void Application::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0, 80.0, 50.0);
    
    // Create the entity manager
    entityMgr = new EntityMgr(mSceneMgr);
    entityMgr->CreateEntity("Alien",     EntityType::ENTITY_ALIEN,     Ogre::Vector3(-200, 0, 0), 1.5);
    entityMgr->CreateEntity("Carrier",   EntityType::ENTITY_CARRIER,   Ogre::Vector3( 100, 0, 0), 1.5);
    entityMgr->CreateEntity("Destroyer", EntityType::ENTITY_DESTROYER, Ogre::Vector3( 400, 0, 0), 1.5);
    entityMgr->CreateEntity("Frigate",   EntityType::ENTITY_FRIGATE,   Ogre::Vector3( 600, 0, 0), 1.5);
    entityMgr->CreateEntity("Speedboat", EntityType::ENTITY_SPEEDBOAT, Ogre::Vector3( 800, 0, 0), 1.5);
    entityMgr->currentEntity = entityMgr->GetEntity("Alien");
    entityMgr->currentEntity->ogreSceneNode->showBoundingBox(true);

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
    float rotate = 0.5f;

    Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_W)) { dirVec.z -= move; }
    if (mKeyboard->isKeyDown(OIS::KC_A)) { dirVec.x -= move; }
    if (mKeyboard->isKeyDown(OIS::KC_S)) { dirVec.z += move; }
    if (mKeyboard->isKeyDown(OIS::KC_D)) { dirVec.x += move; }

    if (mKeyboard->isKeyDown(OIS::KC_R)) { dirVec.y += move; }
    if (mKeyboard->isKeyDown(OIS::KC_F)) { dirVec.y -= move; }

    if (mKeyboard->isKeyDown(OIS::KC_Q)) { cameraNode->yaw(Ogre::Degree(rotate)); }
    if (mKeyboard->isKeyDown(OIS::KC_E)) { cameraNode->yaw(Ogre::Degree(-rotate)); }

    if (mKeyboard->isKeyDown(OIS::KC_Z)) { cameraNode->pitch(Ogre::Degree(rotate)); }
    if (mKeyboard->isKeyDown(OIS::KC_X)) { cameraNode->pitch(Ogre::Degree(-rotate)); }

    cameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& fe) 
{
    mKeyboard->capture();
    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) { return false; }

    mTrayMgr->frameRenderingQueued(fe);

    UpdateCamera(fe);
    UpdateSelectedEntity(fe);
    entityMgr->Tick(fe.timeSinceLastFrame);
    UpdateSelection(fe);
    return true;
}

void Application::UpdateSelectedEntity(const Ogre::FrameEvent& fe) 
{
    static const float speedStep = 0.4;
    static const float headingStep = 0.02;

    keyboardTimer -= fe.timeSinceLastEvent;

    if (entityMgr->entities.size() < 1) return;

    auto entity(entityMgr->currentEntity);

    auto timerElapsed = keyboardTimer < 0;

    if (timerElapsed && mKeyboard->isKeyDown(OIS::KC_UP)) 
    {
        keyboardTimer = keyTime;
        entityMgr->currentEntity->desiredSpeed += speedStep;
        if (entity->desiredSpeed > entity->maxSpeed)
        {
            entity->desiredSpeed = entity->maxSpeed;
        }
    }

    if (timerElapsed && mKeyboard->isKeyDown(OIS::KC_DOWN)) 
    {
        keyboardTimer = keyTime;
        entityMgr->currentEntity->desiredSpeed -= speedStep;
        if (entity->desiredSpeed < entity->minSpeed)
        {
            entity->desiredSpeed = entity->minSpeed;
        }
    }

    if (timerElapsed && mKeyboard->isKeyDown(OIS::KC_LEFT))
    {
        entity->desiredHeading += headingStep;
    }

    if (timerElapsed && mKeyboard->isKeyDown(OIS::KC_RIGHT))
    {
        entity->desiredHeading -= headingStep;
    }
}

void Application::UpdateSelection(const Ogre::FrameEvent& fe)
{
    cycleTimer -= fe.timeSinceLastFrame;
    
    auto timerElapsed = cycleTimer < 0;
    if(timerElapsed && mKeyboard->isKeyDown(OIS::KC_TAB))
    {
        cycleTimer = cycleTime;
        auto currentEntity = entityMgr->currentEntity;
        auto lastEntityIter = entityMgr->entities.end();
        --lastEntityIter;
        auto lastEntity = lastEntityIter->second;
        currentEntity->ogreSceneNode->showBoundingBox(false);
        if (currentEntity->entityId == lastEntity->entityId)
        {
            entityMgr->currentEntity = entityMgr->entities.begin()->second;
        }
        else
        {
            auto nextEntityIter = entityMgr->entities.find(currentEntity->entityId);
            ++nextEntityIter;
            auto nextEntity = nextEntityIter->second;
            entityMgr->currentEntity = nextEntity;
        }
        entityMgr->currentEntity->ogreSceneNode->showBoundingBox(true);
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
    groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
    //groundEntity->setMaterialName("OceanHLSL_GLSL");
    //groundEntity->setMaterialName("Ocean2_Cg");
    //groundEntity->setMaterialName("NavyCg");

}

void Application::MakeSky() 
{
    mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
}

void Application::MakeFog()
{
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);
    mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}
