//============================================
// Name        : GfxMgr.h 
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "mgr.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#  include <OGRE/SdkTrays.h>
#  include <OGRE/SdkCameraMan.h>
#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>
#endif

class InputMgr : 
	public Mgr,
	public Ogre::WindowEventListener,
	public Ogre::FrameListener 
{

public:

	InputMgr(Engine *eng) : Mgr(eng) {}

	void tick(float dt);
	void initialize(Ogre::RenderWindow* _window, Ogre::Root* _root);
	void load_level();
	void stop();

	bool receivedAbort;
	Ogre::Root* root;
	Ogre::RenderWindow* window;
	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

private:
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

};
