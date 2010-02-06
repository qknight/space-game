#include "updatesceneframelistener.h"
#include "mylogger.h"
#include "konstanten.h"

UpdateSceneFrameListener::UpdateSceneFrameListener(RenderWindow* win, Camera* cam, SceneManager* sceneMgr, Game* modle): ExampleFrameListener(win, cam, false,false)
{
  CamPosition = CAMFOLLOW;
//  CamPosition = 3;
  this->Zoom = 500;
  mMouse->capture();
  mKeyboard->capture();
  game = modle;
  player = new Player(game, PLAYERHEAVINESS);
  player->teleport(Vector2(-5500,5500));
  player->accelerate(Vector2(5,-5));
  game->addLightObject(player);
  mCamNode = cam->getParentSceneNode();
//   if (player->tryGetNode() != NULL){
//     mCamNode->detachObject(cam);
//     mCamNode = player->tryGetNode();
//     mCamNode->attachObject(cam);
//   }
    
  this->showDebugOverlay(false);
  
  movableObject *Sun = new movableObject("SUN", SUNHEAVINESS);
  Sun->teleport(Vector2(0,0));
  game->addHeavyObject(Sun);
  
  movableObject *Planet = new movableObject("Planet", PLANETHEAVINESS);
  Planet->circle = true;
  Planet->setCircleRadius(6500);
  Planet->setGravitationPartner(Sun);
  
  Planet->circlespeed = 0.009;
  
  game->addHeavyObject(Planet);
						  
  movableObject *Moon = new movableObject("Moon", 1500000000000);
//  Moon->teleport(Vector2(1000,0));
  Moon->circle = true;
  Moon->setCircleRadius(1000);
  Moon->setGravitationPartner(Planet);
  
  Moon->circlespeed = 0.021;
  
  game->addHeavyObject(Moon); 

  movableObject *Komet = new movableObject("Komet", 4000000000000);
  Komet->circle = true;
  Komet->a = 4000;
  Komet->b = 6300;
  Komet->circlespeed = 0.01;
  movableObject *Hack = new movableObject("Hack", 0);
  Hack->teleport(Vector2(0,28000));
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
  this->game->removeOutOfAreaObjects();
  
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
    
    SceneNode *node = this->mSceneMgr->getRootSceneNode()->createChildSceneNode(str.str());
    Entity *ent;
    if (objName == "Player"){
	node->pitch(Degree(90));
	player->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("player"+str.str(),"razor.mesh");
    }else if (objName == "projectile"){
	node->scale(Vector3(5,5,5));
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("projectile" + str.str(),"Barrel.mesh");
    }else if(objName == "Planet"){
	node->scale(Vector3(3,3,3));
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("Planet" + str.str(),"sphere.mesh");
    }else if(objName == "SUN"){
	node->scale(Vector3(55,55,55));
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("SUN" + str.str(),"Abstrikes.mesh");
	
	Light* myLight = mSceneMgr->createLight("nameOfTheLight");
	myLight->setType(Light::LT_POINT);
	//myLight->setPosition(200, 300, 400);
	myLight->setDiffuseColour(1, 0.5, 0.2);
	myLight->setSpecularColour(1, 0.5, 0.2);
	
	node->attachObject(myLight);
	
    }else if(objName == "Moon"){
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("Moon" + str.str(),"sphere.mesh");
    }else if(objName == "Komet"){
	node->scale(0.281,0.41,0.8);
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
	ent = mSceneMgr->createEntity("Komet" + str.str(),"sphere.mesh");
    }
    node->attachObject(ent);
    node->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
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
      vec *=SPEEDBOOSTSTRENGTH;
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
    this->Zoom += Zoom/10;
  }
   if(mKeyboard->isKeyDown(OIS::KC_PGDOWN) && (Zoom > 50)){
    this->Zoom -= Zoom/10;
  }
  
  
  //Naechstes Leben
  if (mKeyboard->isKeyDown(OIS::KC_SPACE) && player->isDead()){
      this->player->teleport(Vector2(rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE,rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE));
      this->player->setSpeed(Vector2(rand()%3, rand()%3));
      this->player->awake();
  }
  return true;
}
void UpdateSceneFrameListener::moveMyCamera(){
  switch (CamPosition){
    case CAMTOPVIEW:{
	int x = this->player->getPosition().x;
	int y = this->player->getPosition().y;
	this->mCamera->setPosition(Vector3(x, y,SPIELEBENE + Zoom));
	this->mCamera->lookAt(Vector3(x,y,SPIELEBENE));
      }
      break;
    case CAMFOLLOW:{
	float x = this->player->getPosition().x;
	float y = this->player->getPosition().y;
	Vector2 locat = player->getSpeed();
	if (!locat.isZeroLength())
	  locat.normalise();
	
	float sX = locat.x * 1500 + Zoom *locat.x/50;
	float sY = locat.y * 1500 + Zoom *locat.y/50;
	
	this->mCamera->setPosition(Vector3(x - sX, y - sY,SPIELEBENE + Zoom));
	this->mCamera->lookAt(Vector3(x + sX ,y +sY,SPIELEBENE));
	this->mCamera->setNearClipDistance(5);
      }
      break;
  }
  
}