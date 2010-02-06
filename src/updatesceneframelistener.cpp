#include "updatesceneframelistener.h"
#include "mylogger.h"
#include "konstanten.h"

UpdateSceneFrameListener::UpdateSceneFrameListener(RenderWindow* win, Camera* cam, SceneManager* sceneMgr, Game* modle): ExampleFrameListener(win, cam, false,false)
{
  CamPosition = CAMFOLLOW;
//  CamPosition = 3;
  this->Zoom = 0;
  mMouse->capture();
  mKeyboard->capture();
  game = modle;
  player = new Player(game, PLAYERHEAVINESS);
  player->teleport(Vector2(5500,5500));
  player->accelerate(Vector2(-5,-5));
  game->addLightObject(player);
  mCamNode = cam->getParentSceneNode();
  if (player->tryGetNode() != NULL){
    mCamNode->detachObject(cam);
    mCamNode = player->tryGetNode();
    mCamNode->attachObject(cam);
  }
    
  this->showDebugOverlay(false);
  

    
  movableObject *Sun = new movableObject("SUN", SUNHEAVINESS);
  Sun->teleport(Vector2(0,0));
  game->addHeavyObject(Sun);
  
  movableObject *Planet = new movableObject("Planet", PLANETHEAVINESS);
  Planet->circle = true;
  Planet->setCircleRadius(5000);
  Planet->setGravitationPartner(Sun);
  
  Planet->circlespeed = 0.001;
  
  game->addHeavyObject(Planet);
						  
  movableObject *Moon = new movableObject("Moon", 1500000000000);
//  Moon->teleport(Vector2(1000,0));
  Moon->circle = true;
  Moon->setCircleRadius(1000);
  Moon->setGravitationPartner(Planet);
  
  Moon->circlespeed = 0.009;
  
  game->addHeavyObject(Moon); 

  movableObject *Komet = new movableObject("Komet", 4000000000000);
  Komet->circle = true;
  Komet->a = 2000;
  Komet->b = 6300;
  Komet->circlespeed = 0.01;
  movableObject *Hack = new movableObject("Hack", 0);
  Hack->teleport(Vector2(0,8000));
  Komet->setGravitationPartner(Sun);
  
  game->addHeavyObject(Komet);
  
  this->mSceneMgr = sceneMgr;
  this->NodesNum = 0;
  
  this->mCamNode = this->player->tryGetNode();
  if (this->mCamNode = NULL)
    cout << "PLAYER NODE NICHT GESETZT!";
    
  
  
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
  this->game->moveHeavyObjects();
  
  this->moveCamera();
  this->moveMyCamera();
  
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
	nodePlayer->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
    }else if (objName == "projectile"){
//	mylogger::log("projectile "+ str.str());
	
	SceneNode *nodeProj = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("ProjectieleNode" + str.str());
	nodeProj->scale(Vector3(5,5,5));
	nodeProj->pitch(Degree(90));
	obj->addNotifier(new movObjChangedNotifier(nodeProj));
	Entity *Proj = mSceneMgr->createEntity("projectile" + str.str(),"Barrel.mesh");
	nodeProj->attachObject(Proj);
	nodeProj->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
    }else if(objName == "Planet"){
//	mylogger::log("Planet "+ str.str());
	SceneNode *nodePlan = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("PlanetNode" + str.str());
	nodePlan->scale(Vector3(3,3,3));
	obj->addNotifier(new movObjChangedNotifier(nodePlan));
	Entity *Planet = mSceneMgr->createEntity("Planet" + str.str(),"sphere.mesh");
	nodePlan->attachObject(Planet);
	nodePlan->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
    }else if(objName == "SUN"){
//	mylogger::log("Planet "+ str.str());
	SceneNode *nodeSUN = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("SUNNode" + str.str());
	nodeSUN->scale(Vector3(55,55,55));
	obj->addNotifier(new movObjChangedNotifier(nodeSUN));
	Entity *SUN = mSceneMgr->createEntity("SUN" + str.str(),"Abstrikes.mesh");
	nodeSUN->attachObject(SUN);
	nodeSUN->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
    }else if(objName == "Moon"){
//	mylogger::log("Planet "+ str.str());
	SceneNode *nodeMoon = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("MoonNode" + str.str());
//	nodeMoon->scale(1,1,1);
	obj->addNotifier(new movObjChangedNotifier(nodeMoon));
	Entity *moon = mSceneMgr->createEntity("Moon" + str.str(),"sphere.mesh");
	nodeMoon->attachObject(moon);
	nodeMoon->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
    }else if(objName == "Komet"){
//	mylogger::log("Planet "+ str.str());
	SceneNode *nodeKomet = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("KometNode" + str.str());
	nodeKomet->scale(0.381,0.41,0.5);
	obj->addNotifier(new movObjChangedNotifier(nodeKomet));
	Entity *komet = mSceneMgr->createEntity("Komet" + str.str(),"sphere.mesh");
	nodeKomet->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
	nodeKomet->attachObject(komet);
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
 
  if (mKeyboard->isKeyDown(OIS::KC_SPACE)){
    if (player->BoostAvaible())
      vec *=SPEEDBOOST;
  }
  player->accelerate(vec);
  
  
  //Cam Positionen
  if(mKeyboard->isKeyDown(OIS::KC_F1)){
    this->CamPosition = CAMTOPVIEW;
  }
  if(mKeyboard->isKeyDown(OIS::KC_F2)){
    this->CamPosition = CAMFOLLOW;
    
    this->mCamera->roll(Radian(90));
  }
  //Zoom in der CAMTOPVIEW
  if(mKeyboard->isKeyDown(OIS::KC_PGUP)){
    this->Zoom += 500;
  }
   if(mKeyboard->isKeyDown(OIS::KC_PGDOWN)){
    this->Zoom -= 500;
  }
  return true;
}
void UpdateSceneFrameListener::moveMyCamera(){
  switch (CamPosition){
    case CAMTOPVIEW:{
	int x = this->player->getPosition().x;
	int y = this->player->getPosition().y;
	this->mCamera->setPosition(Vector3(x, y, Zoom));
	this->mCamera->lookAt(Vector3(x,y,SPIELEBENE));
      }
      break;
    case CAMFOLLOW:{
	float x = this->player->getPosition().x;
	float y = this->player->getPosition().y;
	Vector2 locat = player->getSpeed();
	if (!locat.isZeroLength())
	  locat.normalise();
	
	float sX = locat.x * 1500;
	float sY = locat.y * 1500;
	
	this->mCamera->setPosition(Vector3(x - sX, y - sY,250 + Zoom/5));
	this->mCamera->lookAt(Vector3(x + sX ,y +sY,SPIELEBENE));
	this->mCamera->setNearClipDistance(5);
      }
      break;
  }
  
}