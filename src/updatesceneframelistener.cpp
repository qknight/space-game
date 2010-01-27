#include "updatesceneframelistener.h"
#include "mylogger.h"
#include "konstanten.h"

UpdateSceneFrameListener::UpdateSceneFrameListener(RenderWindow* win, Camera* cam, SceneManager* sceneMgr, Game* modle): ExampleFrameListener(win, cam, false,false)
{
  mMouse->capture();
  mKeyboard->capture();
  game = modle;
  player = new Player(game, PLAYERHEAVINESS);
  player->teleport(Vector2(1000,1000));
  game->addLightObject(player);
  
  movableObject *Planet = new movableObject("Planet", PLANETHEAVINESS);
  game->addHeavyObject(Planet);
  
  this->mSceneMgr = sceneMgr;
  this->NodesNum = 0;
  

    
}

// Overriding the default processUnbufferedKeyInput so the key updates we define
// later on work as intended.
bool UpdateSceneFrameListener::processUnbufferedKeyInput(const Ogre::FrameEvent& evt)
{
//return ExampleFrameListener::processUnbufferedKeyInput(evt);
  return true;
}


// Overriding the default processUnbufferedMouseInput so the Mouse updates we define
// later on work as intended. 
bool UpdateSceneFrameListener::processUnbufferedMouseInput(const Ogre::FrameEvent& evt)
{
  return ExampleFrameListener::processUnbufferedMouseInput(evt);
//  return true;
}


bool UpdateSceneFrameListener::frameStarted(const FrameEvent &evt)
{      
  if (this->player == NULL){
    return false;
  }
  
  bool ret = this->KeyInput();
  this->getNewObjects(); 
    
  this->game->moveLightObjects();
  
  if (this->player == NULL){
    return false;
  }
  return ret;
}

void UpdateSceneFrameListener::getNewObjects()
{
  while (this->game->hasNewObject()){
    movableObject *obj = game->getNextNewObject();
    String objName = obj->getObjektName();
 //   mylogger::log("newObject");
    
    std::stringstream str; 
    str<<NodesNum; 
    
    
    if (objName == "Player"){
//	mylogger::log("player "+ str.str());
	
	SceneNode *nodePlayer = this->mSceneMgr->getRootSceneNode()->createChildSceneNode(str.str());
	nodePlayer->pitch(Degree(90));
	player->addNotifier(new movObjChangedNotifier(nodePlayer));
	Entity *ship = mSceneMgr->createEntity("player"+str.str(),"razor.mesh");
	nodePlayer->attachObject(ship);
    }else if (objName == "projectile"){
//	mylogger::log("projectile "+ str.str());
	
	SceneNode *nodeProj = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("ProjectieleNode" + str.str());
	nodeProj->scale(Vector3(5,5,5));
	nodeProj->pitch(Degree(90));
	obj->addNotifier(new movObjChangedNotifier(nodeProj));
	Entity *Proj = mSceneMgr->createEntity("projectile" + str.str(),"Barrel.mesh");
	nodeProj->attachObject(Proj);
    }else if(objName == "Planet"){
//	mylogger::log("Planet "+ str.str());
	
	SceneNode *nodePlan = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("PlanetNode" + str.str());
	nodePlan->scale(Vector3(2,2,2));
	obj->addNotifier(new movObjChangedNotifier(nodePlan));
	Entity *Planet = mSceneMgr->createEntity("Planet" + str.str(),"sphere.mesh");
	nodePlan->attachObject(Planet);
	nodePlan->setPosition(Vector3(0,0,SPIELEBENE));
    }
    
    NodesNum++;
  }
}

bool UpdateSceneFrameListener::KeyInput()
{

  if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
     return false;

  
  Vector2 vec;
  
  //Schüsse abfeuern
  vec.x = 0;
  vec.y = 0;
  if(mKeyboard->isKeyDown(OIS::KC_W)){
    vec.y += 1;
  }
  if(mKeyboard->isKeyDown(OIS::KC_S)){
    vec.y -= 1;
  }
  if(mKeyboard->isKeyDown(OIS::KC_A)){
    vec.x -= 1;
  }
  if(mKeyboard->isKeyDown(OIS::KC_D)){
    vec.x += 1;
  }
  if (!vec.isZeroLength()){
    vec.normalise();
    projectile * proj = new projectile(PROJECTIELESPEED,vec, MUNITIONSHEAVINESS);
    if (!player->fireWappon(proj))
      player->reload();
  }else{
    player->reload();
  }
  
  //Lenken
  vec.x = 0;
  vec.y = 0;
  if(mKeyboard->isKeyDown(OIS::KC_UP)){
    vec.y += 1.0;
  }
  if(mKeyboard->isKeyDown(OIS::KC_DOWN)){
    vec.y -= 1.0f;    
  }
  if(mKeyboard->isKeyDown(OIS::KC_LEFT)){
    vec.x -= 1.0f;
  }
  if(mKeyboard->isKeyDown(OIS::KC_RIGHT)){
    vec.x += 1.0f;
  }
  vec.normalise();
  vec *= SPIELERBESCHLEUNIGUNG;
  player->accelerate(&vec);
  return true;
}
