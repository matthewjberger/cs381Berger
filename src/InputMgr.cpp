/*
 * inputMgr.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#include "inputMgr.h"
#include "engine.h"


InputMgr::InputMgr(Engine *engine) : Mgr(engine){
	keyboardTimer = keyTime;
	selectionTimer = selectionTime;

    keyTime = 0.2f;
    selectionTime = 0.2f;

	keyboard = 0;
	mouse = 0;
	oisInputManager = 0;

	OIS::ParamList pl;
	size_t windowHandle = 0;
	std::ostringstream windowHandleStr;
	engine->gfxMgr->ogreRenderWindow->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleStr << windowHandle;

	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	// insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	oisInputManager = OIS::InputManager::createInputSystem(pl);
	keyboard = static_cast<OIS::Keyboard*>(oisInputManager->createInputObject(OIS::OISKeyboard, true));
	mouse    = static_cast<OIS::Mouse*>(oisInputManager->createInputObject(OIS::OISMouse, true));

	keyboard->setEventCallback(this);
	mouse->setEventCallback(this);

	windowResized(engine->gfxMgr->ogreRenderWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);

}

InputMgr::~InputMgr(){ // before gfxMgr destructor

}

void InputMgr::init(){

}

void InputMgr::loadLevel(){

}

void InputMgr::tick(float dt){

	keyboard->capture();
	mouse->capture();
	if(keyboard->isKeyDown(OIS::KC_ESCAPE))
		engine->stop();

	UpdateCamera(dt);
	UpdateDesiredSpeedHeading(dt);
	//UpdateSelection(dt);

}

void InputMgr::stop(){
	if (oisInputManager){
		oisInputManager->destroyInputObject(mouse);
		oisInputManager->destroyInputObject(keyboard);
		OIS::InputManager::destroyInputSystem(oisInputManager);
		oisInputManager = 0;
	}
}

void InputMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputMgr::windowClosed(Ogre::RenderWindow* rw){
	//Ogre::WindowEventUtilities::removeWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
	if(rw == engine->gfxMgr->ogreRenderWindow){
		engine->stop();
	}
}

bool InputMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool InputMgr::keyReleased(const OIS::KeyEvent &arg){
	std::cout << "Checking key release" << std::endl;
	if (arg.key == OIS::KC_TAB){
		engine->entityMgr->SelectNextEntity();
	}
	return true;
}
bool InputMgr::mouseMoved(const OIS::MouseEvent &arg){
	return true;
}
bool InputMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}
bool InputMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

// Game specific input handling
void InputMgr::UpdateCamera(float dt){
	float move = 100.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (keyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (keyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (keyboard->isKeyDown(OIS::KC_E))
	    dirVec.y += move;

	  if (keyboard->isKeyDown(OIS::KC_F))
	    dirVec.y -= move;

	  if (keyboard->isKeyDown(OIS::KC_A))
	  {
	    if (keyboard->isKeyDown(OIS::KC_LSHIFT))
		      engine->gfxMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));
	    else
	      dirVec.x -= move;
	  }

	  if (keyboard->isKeyDown(OIS::KC_D))
	  {
	    if (keyboard->isKeyDown(OIS::KC_LSHIFT))
	      engine->gfxMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));
	    else
	      dirVec.x += move;
	  }

	  engine->gfxMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);

}

void InputMgr::UpdateDesiredSpeedHeading(float dt){
	keyboardTimer -= dt;

	if(engine->entityMgr->selectedEntity){

		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD8)){
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed += 10;
		}
		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD2)){
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed -= 10;
		}
		engine->entityMgr->selectedEntity->desiredSpeed =
				std::max(engine->entityMgr->selectedEntity->minSpeed,
						std::min(engine->entityMgr->selectedEntity->maxSpeed,
								engine->entityMgr->selectedEntity->desiredSpeed));


		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD4)){
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading -= 0.3f;
		}
		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD6)){
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading += 0.3f;
		}
		//entityMgr->selectedEntity->desiredHeading = FixAngle(entityMgr->selectedEntity->desiredHeading);
	}

}

void InputMgr::UpdateSelection(float dt){
	selectionTimer -= dt;
	if(selectionTimer < 0 && keyboard->isKeyDown(OIS::KC_TAB)){
		selectionTimer = this->selectionTime;
		engine->entityMgr->SelectNextEntity();
	}
}




