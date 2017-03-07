//============================================
// Name        : Application.cpp
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
// Description : Assignment 1                 
//============================================

#ifndef __Application_h_
#define __Application_h_

#include "BaseApplication.h"

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
  void UpdateVelocity(const Ogre::FrameEvent& fe);
  void UpdatePosition(const Ogre::FrameEvent& fe);
  void CopyPositionToSceneNode();



  //------------------------------------------------------------

  Ogre::SceneNode* cubeSceneNode;
  Ogre::SceneNode* cameraNode;
  Ogre::Vector3 velocity;
  Ogre::Vector3 position;
  float yaw;
  float deltaVelocity;
  float keyboardTimer;
  float keyTime;

protected:
  virtual void createScene();
  //virtual void createCamera();
  //virtual void createViewports();
};

#endif // #ifndef __Application_h_
