#include "spaceview.h"
#include "mylogger.h"

SpaceView::SpaceView(Game* modle):ExampleApplication() {
  this->modle = modle;
//   std::cout << "XXX" << __FILE__ << ":" << __FUNCTION__;

}

SpaceView::~SpaceView() {
  
}

void SpaceView::createScene(void)
{
  mSceneMgr->setAmbientLight(ColourValue(1,1,1));
  /*
  Entity *ent3 = mSceneMgr->createEntity("Schiff","razor.mesh");
  SceneNode *node3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("SchiffNode",Vector3(50,50,-1500));
//      node3->scale(5,5,5);
  node3->pitch(Degree(70));
  //node3->yaw(Degree(30));
  // node3->roll(Degree(-30));
  node3->attachObject(ent3);


  Entity *ent1 = mSceneMgr->createEntity("Geschützturm","RZR-002.mesh");
  SceneNode *node1 = node3->createChildSceneNode("GeschützturmNode");
  node1->scale(1,1,1);
  node1->attachObject(ent1);
//   node1->yaw(Degree(90));
  node1->setPosition(Vector3(-8,20,-10));

  
/*     Entity *ent1 = mSceneMgr->createEntity( "Robot", "robot.mesh" );
    SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "RobotNode" );
    node1->attachObject( ent1 );

//   node1->scale( .5, 1, 2 ); 

    Entity *ent2 = mSceneMgr->createEntity( "Robot2", "robot.mesh" );
    SceneNode *node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "RobotNode2", Vector3( 50, 50, 50 ) );
    node2->attachObject( ent2 );

//       node2->scale( 1, 2, 1 );*/
//   std::cout <<  "XXX" << __FILE__ << ":" << __FUNCTION__;

}

void SpaceView::createCamera(void )
{
  // create camera, but leave at default position
  mCamera = mSceneMgr->createCamera("PlayerCam"); 
  mCamera->setNearClipDistance(5);
//   std::cout <<  "XXX" << __FILE__ << ":" << __FUNCTION__;
}

void SpaceView::createFrameListener(void )
{
  // Create the FrameListener
  mFrameListener = new UpdateSceneFrameListener(mWindow, mCamera, mSceneMgr, modle);
  mFrameListener->showDebugOverlay(true);
  mRoot->addFrameListener(mFrameListener);
//   std::cout <<  "XXX" << __FILE__ << ":" << __FUNCTION__;
}
