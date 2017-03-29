//============================================
// Name        : GfxMgr.h 
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================
#pragma once

#include "mgr.h"
#include "GlobalIncludes.h"

class InputMgr :
    public Mgr,
    public Ogre::WindowEventListener,
    public Ogre::FrameListener
    //public OIS::KeyListener,
    //public OIS::MouseListener,
    //OgreBites::SdkTrayListener
{

public:

    InputMgr(Engine *eng) :
        Mgr(eng),
        keyTime(0.2f),
        selectionTime(0.2f),
        keyboardTimer(keyTime),
        selectionTimer(selectionTime)
    {}

    void tick(float dt) override;
    void init() override;
    void loadLevel() override;
    void stop() override;

    Ogre::Root* root;
    Ogre::RenderWindow* window;
    OIS::InputManager* mInputManager;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;

private:
    void windowResized(Ogre::RenderWindow* rw) override;
    void windowClosed(Ogre::RenderWindow* rw) override;

    bool frameRenderingQueued(const Ogre::FrameEvent& fe) override;
    void updateDesiredSpeedHeading(const Ogre::FrameEvent& fe);
    void updateSelection(float dt);;
    void updateCamera(const Ogre::FrameEvent& fe);

    float keyTime;
    float selectionTime;
    float keyboardTimer;
    float selectionTimer;
    Ogre::Vector3 position;
    Ogre::Vector3 velocity;
};