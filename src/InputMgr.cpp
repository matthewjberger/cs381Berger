//============================================
// Name        : InputMgr.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "inputMgr.h"

void InputMgr::tick(float dt)
{
	if (window->isClosed())
		return;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Pressed Escape.");
		receivedAbort = true;
	}
}

void InputMgr::initialize(Ogre::RenderWindow* _window, Ogre::Root* _root)
{
	receivedAbort = false;
	window = _window;
	root = _root;
	mInputManager = 0;
	mMouse = 0;
	mKeyboard = 0;

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

void InputMgr::load_level()
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