//============================================
// Name        : Application.h
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
  virtual ~Application();
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

  void MakeGround();
  void MakeSky();
  void MakeFog();
  void UpdateCamera(const Ogre::FrameEvent& fe);
  void UpdateEntityMgr(const Ogre::FrameEvent& fe);

  //------------------------------------------------------------

  std::shared_ptr<EntityMgr> entityMgr;
  Ogre::SceneNode* cubeSceneNode;
  Ogre::SceneNode* cameraNode;
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  float yaw;
  float deltaVelocity;
  float keyboardTimer;
  float keyTime;

protected:
  virtual void createScene();
  //virtual void createViewports();
};

#endif // #ifndef __Application_h_
