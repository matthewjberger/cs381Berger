/*
 * inputMgr.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include "mgr.h"

class InputMgr : public Mgr, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener, public Ogre::FrameListener
{
private:
	void UpdateCamera(float dt);
	void UpdateDesiredSpeedHeading(float dt);
	void UpdateSelection(float dt);
    void PerformRayCast();
	float keyboardTimer;
	float selectionTimer;
	float keyTime;
	float selectionTime;

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

public:

	InputMgr(Engine *engine);
	~InputMgr();
	virtual void init();
	virtual void tick(float dt);
	virtual void loadLevel();
	virtual void stop();

	//OIS Input devices
	OIS::InputManager* oisInputManager;
    OIS::Mouse*        mouse;
    OIS::Keyboard*     keyboard;

    // Ogre bites
    OgreBites::SdkTrayManager* trayManager;
    OgreBites::InputContext inputContext;
};



#endif /* INPUTMGR_H_ */
