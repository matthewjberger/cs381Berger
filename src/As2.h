//============================================
// Name        : As2.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#ifndef __Application_h_
#define __Application_h_

#include "BaseApplication.h"
#include "EntityMgr.h"

class Application : public BaseApplication
{
public:
  Application();
  bool frameRenderingQueued(const Ogre::FrameEvent& fe) override;

  void MakeGround();
  void MakeSky();
  void MakeFog();
  void UpdateCamera(const Ogre::FrameEvent& fe);
  void UpdateSelectedEntity(const Ogre::FrameEvent& fe);
  void UpdateSelection(const Ogre::FrameEvent& fe);

  bool keyPressed(const OIS::KeyEvent &arg) override { return true; }
  bool keyReleased(const OIS::KeyEvent &arg) override { return true; }

  EntityMgr* entityMgr;
  Ogre::SceneNode* cubeSceneNode;
  Ogre::SceneNode* cameraNode;
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  float yaw;
  float deltaVelocity;
  float keyboardTimer;
  float keyTime;
  float cycleTimer;
  float cycleTime;

protected:
  void createScene() override;
};

#endif // #ifndef __Application_h_
