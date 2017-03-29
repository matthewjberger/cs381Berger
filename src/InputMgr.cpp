//============================================
// Name        : InputMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "InputMgr.h"
#include "engine.h"

void InputMgr::tick(float dt)
{
    if (window->isClosed())
        return;

    mKeyboard->capture();
    mMouse->capture();

    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        Ogre::LogManager::getSingletonPtr()->logMessage("Pressed Escape.");
        engine->keepRunning = false;
    }
}

void InputMgr::init()
{
    window = engine->gfxMgr->mWindow;
    root = engine->gfxMgr->mRoot;
    mInputManager = nullptr;
    mMouse = nullptr;
    mKeyboard = nullptr;

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));

    //Set initial mouse clipping size
    windowResized(window);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(window, this);
    root->addFrameListener(this);
}

void InputMgr::loadLevel()
{
}

void InputMgr::stop()
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
    windowClosed(window);
}

//Adjust mouse clipping area
void InputMgr::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if (rw == window)
    {
        if (mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

bool InputMgr::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    mKeyboard->capture();
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        engine->keepRunning = false;
        return false;
    }
    updateCamera(fe);
    updateDesiredSpeedHeading(fe);
    updateSelection(fe.timeSinceLastFrame);
    return true;
}

void InputMgr::updateDesiredSpeedHeading(const Ogre::FrameEvent& fe)
{
    keyboardTimer -= fe.timeSinceLastEvent;

    if (engine->entityMgr->selectedEntity) {

        if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)) {
            keyboardTimer = keyTime;
            engine->entityMgr->selectedEntity->desiredSpeed += 10;
        }
        if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) {
            keyboardTimer = keyTime;
            engine->entityMgr->selectedEntity->desiredSpeed -= 10;
        }
        engine->entityMgr->selectedEntity->desiredSpeed = std::max(engine->entityMgr->selectedEntity->minSpeed,
            std::min(engine->entityMgr->selectedEntity->maxSpeed, engine->entityMgr->selectedEntity->desiredSpeed));


        if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)) {
            keyboardTimer = keyTime;
            engine->entityMgr->selectedEntity->desiredHeading -= 0.3f;
        }
        if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)) {
            keyboardTimer = keyTime;
            engine->entityMgr->selectedEntity->desiredHeading += 0.3f;
        }
        //entityMgr->selectedEntity->desiredHeading = FixAngle(entityMgr->selectedEntity->desiredHeading);
    }
}

void InputMgr::updateSelection(float dt)
{
    selectionTimer -= dt;
    if (selectionTimer < 0 && mKeyboard->isKeyDown(OIS::KC_TAB)) {
        selectionTimer = this->selectionTime;
        engine->entityMgr->SelectNextEntity();
    }
}

void InputMgr::updateCamera(const Ogre::FrameEvent& fe)
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

    if (mKeyboard->isKeyDown(OIS::KC_Q)) { engine->gfxMgr->mCameraNode->yaw(Ogre::Degree(rotate)); }
    if (mKeyboard->isKeyDown(OIS::KC_E)) { engine->gfxMgr->mCameraNode->yaw(Ogre::Degree(-rotate)); }

    if (mKeyboard->isKeyDown(OIS::KC_Z)) { engine->gfxMgr->mCameraNode->pitch(Ogre::Degree(rotate)); }
    if (mKeyboard->isKeyDown(OIS::KC_X)) { engine->gfxMgr->mCameraNode->pitch(Ogre::Degree(-rotate)); }

    engine->gfxMgr->mCameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}
