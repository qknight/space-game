#include "updatesceneframelistener.h"
#include "mylogger.h"
#include "konstanten.h"
#include <OgreTextAreaOverlayElement.h>
#include "spielfeldumrandung.h"

UpdateSceneFrameListener::UpdateSceneFrameListener(RenderWindow* win, Camera* cam, SceneManager* sceneMgr, Game* modle): ExampleFrameListener(win, cam, false,false)
{
    CamPosition = DYNAMICCAMFOLLOW;
//  CamPosition = 3;
    this->Zoom = 13000;
//   mMouse->capture();

    mKeyboard->capture();
    if (mJoy)
        mJoy->capture();
    game = modle;
    player = new Player(game, PLAYERHEAVINESS);
    player->teleport(Vector2(-5500,5500));
    //player->accelerate(Vector2(5,-5));
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
    Planet->setCircleRadius(7500);
    Planet->setGravitationPartner(Sun);
    Planet->circlespeed = 0.009;
    game->addHeavyObject(Planet);
    { 
      movableObject *Planet2 = new movableObject("Planet", PLANETHEAVINESS);
      Planet2->circle = true;
      Planet2->setCircleRadius(30500);
      Planet2->setGravitationPartner(Sun);
      Planet2->circlespeed = 0.0033;
      game->addHeavyObject(Planet2);
      movableObject *Moon = new movableObject("Moon", 1500000000000);
  //  Moon->teleport(Vector2(1000,0));
      Moon->circle = true;
      Moon->setCircleRadius(2300);
      Moon->setGravitationPartner(Planet2);

      Moon->circlespeed = 0.011;

      game->addHeavyObject(Moon);
    }
    {
      movableObject *Komet = new movableObject("Komet", 4000000000000);
      Komet->circle = true;
      Komet->a = 17000;
      Komet->b = 21000;
      Komet->circlespeed = 0.0021;
      Komet->setGravitationPartner(Sun);
      game->addHeavyObject(Komet);
    }
    
    {
      movableObject *Moon = new movableObject("Moon", 150000000000000);
  //  Moon->teleport(Vector2(1000,0));
      Moon->circle = true;
      Moon->setCircleRadius(1300);

      Moon->circlespeed = 0.011;
      Moon->teleport(Vector2(7000,7000));
      game->addHeavyObject(Moon);
      
      movableObject *Moon2 = new movableObject("Moon", 150000000000000);
  //  Moon->teleport(Vector2(1000,0));
      Moon2->circle = true;
      Moon2->setCircleRadius(1300);
      Moon2->teleport(Vector2(7100,7100));

      Moon2->circlespeed = 0.011;

      Moon2->setGravitationPartner(Moon);
      Moon->setGravitationPartner(Moon2);
      game->addHeavyObject(Moon2);
    }
      
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

// http://www.ogre3d.org/wiki/index.php/Tutorial_5
  //  this->mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
  //  this->mSceneMgr->setSkyBox(true, "SkyBox/Hubble1");
  
   Plane plane;
   plane.d = 10000;
   plane.normal = Vector3::NEGATIVE_UNIT_X; 
   plane.normal = Vector3::UNIT_Z;
  
  // mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1500, 75);

 //  mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1500, 1, true, 1.5f, 150, 150);
      mSceneMgr->setSkyPlane(true, plane, "SkyBox/test1", 200, 1, true, 1.5f, 150, 150);
  
    
   
    Spielfeldumrandung umrandung(mSceneMgr);
    
    
    this->intersectionQuery = mSceneMgr->createIntersectionQuery();   
    intersectionQuery->setQueryMask(~100);

}

// Overriding the default processUnbufferedKeyInput so the key updates we define
// later on work as intended.
// bool UpdateSceneFrameListener::processUnbufferedKeyInput(const Ogre::FrameEvent& evt)
// {
// //return ExampleFrameListener::processUnbufferedKeyInput(evt);
//   return true;
// }


// Overriding the default processUnbufferedMouseInput so the Mouse updates we define
// later on work as intended.
// bool UpdateSceneFrameListener::processUnbufferedMouseInput(const Ogre::FrameEvent& evt)
// {
//   return ExampleFrameListener::processUnbufferedMouseInput(evt);
// //  return true;
// }


bool UpdateSceneFrameListener::frameStarted(const FrameEvent &evt) {
    if (this->player == NULL) {
        return false;
    }
    if (rand() % 40 == 0)
       game->addLightObject(new metheor());

    // this is needed for timer stuff
    player->reload(); // a weapon needs a few cycles to reload, if a player tries to shoot nothing happens
    // no more timer stuff

    bool ret = this->KeyInput();
    this->JoyInput();
    this->getNewObjects();

    this->game->moveLightObjects();
    this->game->moveHeavyObjects();
    this->game->removeOutOfAreaObjects();
    this->Kolisionen();

    this->moveCamera();
    this->moveMyCamera();
    
//     cout << player->getLife() << " " << this->player->getShild()<<" " <<this->player->getWappon() << endl;
    const int faktor = 7;
    this->myOverlay.Aktuallisieren(faktor*this->player->getLife(), faktor*this->player->getShild(),faktor* this->player->getWappon());
//     this->myOverlay.Aktuallisieren(100, 33, 33);
    if (this->player == NULL) {
        return false;
    }
    return ret;
}
void UpdateSceneFrameListener::Kolisionen() {
//     IntersectionSceneQueryResult& queryResult = mSceneMgr->createIntersectionQuery()->execute();
    IntersectionSceneQueryResult& queryResult = this->intersectionQuery->execute();
    for (std::list<SceneQueryMovableObjectPair>::iterator it = queryResult.movables2movables.begin();it != queryResult.movables2movables.end(); ++it) {
        movableObject * first = Ogre::any_cast<movableObject*>((*it).first->getUserAny());
        movableObject * second = Ogre::any_cast<movableObject*>((*it).second->getUserAny());

        game->kollision(first, second);
    }
}

void UpdateSceneFrameListener::getNewObjects()
{
    int NodesNumOld = NodesNum;
    while (this->game->hasNewObject()) {
        movableObject *obj = game->getNextNewObject();
        String objName = obj->getObjektName();
//   mylogger::log("newObject");

        std::stringstream str;
        str<<NodesNum;

        SceneNode *node = this->mSceneMgr->getRootSceneNode()->createChildSceneNode(str.str());
        Entity *ent;
        if (objName == "Player") {
            //node->pitch(Degree(90));
            node->scale(3,3,3);
            player->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
            ent = mSceneMgr->createEntity("player"+str.str(),"Abstrikes.mesh");
        } else if (objName == "projectile") {
            node->scale(Vector3(0.1,0.1,0.1));
/*            obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));*/
            ent = mSceneMgr->createEntity("projectile" + str.str(),"sphere.mesh");
	    ent->setMaterialName("Wappon/Bunt");
        } else if (objName == "Planet") {
            node->scale(Vector3(3,3,3));
/*            obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));*/
            ent = mSceneMgr->createEntity("Planet" + str.str(),"sphere.mesh");
// 	    ent->setMaterialName("space-game/myMars");
        } else if (objName == "SUN") {
            node->scale(Vector3(15,15,15));
/*            obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));*/
            ent = mSceneMgr->createEntity("SUN" + str.str(),"sphere.mesh");
	    
            Light* myLight = mSceneMgr->createLight("nameOfTheLight");
            myLight->setType(Light::LT_POINT);
            //myLight->setPosition(200, 300, 400);
            myLight->setDiffuseColour(1, 0.5, 0.2);
            myLight->setSpecularColour(1, 0.5, 0.2);
            node->attachObject(myLight);
	    
	    // adds the green lines from here:
	    // http://www.ogre3d.org/wiki/index.php/Fading_Object_Shader
	    ent->setMaterialName("space-game/mySun");
	    Vector4 vColour = Vector4(12, 23, 23, 122);
	    Vector4 vRadius = Vector4(500,0,0,0);
// 	    material->setCustomParameter(0,vColour);
// 	    material->setCustomParameter(1,vRadius);
            ent->setMaterialName("shader/ring");
        } else if (objName == "Moon") {
/*            obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));*/
            ent = mSceneMgr->createEntity("Moon" + str.str(),"sphere.mesh");
// 	    ent->setMaterialName("space-game/myMoon");
        } else if (objName == "Komet") {
            node->scale(0.4,0.4,0.4);
//             obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));
            ent = mSceneMgr->createEntity("Komet" + str.str(),"sphere.mesh");
        } else if (objName ==  "metheor"){
	    node->scale(0.4 +(rand()%3)/2,0.4 +(rand()%3)/2,0.4 +(rand()%3)/2);
	    ent = mSceneMgr->createEntity("metheor"  + str.str(),"sphere.mesh");
	}

        ent->setUserAny(Any(obj));

        node->attachObject(ent);
        node->setPosition(Vector3(obj->getPosition().x,obj->getPosition().y,SPIELEBENE));
        node->setPosition(Vector3(SPIELEBENE,obj->getPosition().x,obj->getPosition().y));
	obj->addNotifier(new movObjChangedNotifier(node, mSceneMgr));

        NodesNum++;
    }
   if (NodesNumOld > NodesNum) {
        mSceneMgr->destroyQuery(intersectionQuery);
        this->intersectionQuery = mSceneMgr->createIntersectionQuery();
	intersectionQuery->setQueryMask(~100);
   }
}

bool UpdateSceneFrameListener::JoyInput() {
  if (js.joy1){
    bool boost;
    // This is needed in the even queue of SDL
    js.joyupdate();
    // now we query for some input
    int k=0;
    for ( int i=0; i < SDL_JoystickNumButtons ( js.joy1 ); ++i ) {
        unsigned int n = SDL_JoystickGetButton ( js.joy1, i );
        if ( n != 0 )
            switch (i) {
                // button 1,2,3,4 on the joypad are 0,1,2,3 internally
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;

                // button 4 and 6 are 'links hinten 1 and links hinten 2'
            case 4:
                this->Zoom += 50 + Zoom/30;
		if (Zoom > 95732)
		  Zoom = 95732;
                break;
            case 6:
                this->Zoom -= 50 + Zoom/30;
		if (Zoom < 3000)
		  Zoom = 3000;
                break;

                // button 5 and 7 are 'rechts hinten 1 and rechts hinten 2'
		// and they are used to shoot laser+projectiles
            case 5:
	       k = 5;
            case 7: 
	       k = 7; 
	      {
                Vector2 vec2;
                for ( int i=0; i < SDL_JoystickNumAxes ( js.joy1 ); ++i ) {
                    signed short a = SDL_JoystickGetAxis ( js.joy1, i );
                    if ( a != 0 ) {
                        if (i == 3)
                            vec2.x += a/12700;
                        if (i == 2)
                            vec2.y -= a/12700;
                    }
                }

//                 cout << vec2.x << " " << vec2.y << endl;
                if (!vec2.isZeroLength()) {
                    vec2.normalise();
                    projectile * proj = new projectile(PROJECTIELESPEED,vec2, MUNITIONSHEAVINESS);
                    proj->Damage = 4;
                    player->fireWappon(proj);
                }
            }

            break;

            case 8: // select
                break;
            case 9: // start
                if (player->isDead()) {
                    this->player->teleport(Vector2(rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE,rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE));
                    //this->player->setSpeed(Vector2(rand()%3, rand()%3));
                    this->player->awake();
                }
                break;

            case 10: // left joystick pressed
                boost = player->BoostAvaible();
                break;
            case 11: // right joystick pressed
                break;

            default:
                break;
            }

    }
    Vector2 vec;

    for ( int i=0; i < SDL_JoystickNumAxes ( js.joy1 ); ++i ) {
        signed short a = SDL_JoystickGetAxis ( js.joy1, i );
        if ( a != 0 ) {
            if (i == 0)
                vec.x += a/12700;
            if (i == 1)
                vec.y -= a/12700;
        }
    }
    if (boost)
        vec *= SPEEDBOOSTSTRENGTH;

    player->accelerate(vec);
  }
    return true;
}

bool UpdateSceneFrameListener::KeyInput()
{

    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;


    Vector2 vec;

    //Schüsse abfeuern

    vec.x = 0;
    vec.y = 0;

    if (mKeyboard->isKeyDown(OIS::KC_W)) {
        vec.y += 1;
    }
    if (mKeyboard->isKeyDown(OIS::KC_S)) {
        vec.y -= 1;
    }
    if (mKeyboard->isKeyDown(OIS::KC_A)) {
        vec.x -= 1;
    }
    if (mKeyboard->isKeyDown(OIS::KC_D)) {
        vec.x += 1;
    } 
    if (mKeyboard->isKeyDown(OIS::KC_F)) {
	game->addLightObject(new metheor());
    }
    if (!vec.isZeroLength()) {
        vec.normalise();
        projectile * proj = new projectile(PROJECTIELESPEED,vec, MUNITIONSHEAVINESS);
       // proj->Damage = 4;
        player->fireWappon(proj);
    }
    //Lenken
    vec.x = 0;
    vec.y = 0;
    if (mKeyboard->isKeyDown(OIS::KC_UP)) {
        vec.y += 1.0;
    }
    if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
        vec.y -= 1.0f;
    }
    if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
        vec.x -= 1.0f;
    }
    if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
        vec.x += 1.0f;
    }
    vec.normalise();
    vec *= SPIELERBESCHLEUNIGUNG;

    if (mKeyboard->isKeyDown(OIS::KC_SPACE)) {
        if (player->BoostAvaible())
            vec *=SPEEDBOOSTSTRENGTH;
    }
    player->accelerate(vec);

    //Cam Positionen
    if (mKeyboard->isKeyDown(OIS::KC_F1)) {
        this->CamPosition = CAMTOPVIEW;
    }
    if (mKeyboard->isKeyDown(OIS::KC_F2)) {
        this->CamPosition = CAMFOLLOW;

    //    this->mCamera->roll(Radian(90));
    }
    if (mKeyboard->isKeyDown(OIS::KC_F3)){
	this->CamPosition = DYNAMICCAMFOLLOW;
    }
    //Zoom in der CAMTOPVIEW
    if (mKeyboard->isKeyDown(OIS::KC_PGUP)) {
        this->Zoom += 50 + Zoom/30;
        if (Zoom > 95732)
          Zoom = 95732;
  //     cout << Zoom << endl;
    }
    if (mKeyboard->isKeyDown(OIS::KC_PGDOWN)) {
        this->Zoom -= 50 + Zoom/30;
	if (Zoom < 3000)
	  Zoom = 3000;
  //      cout << Zoom << endl;
    }

    if (mKeyboard->isKeyDown(OIS::KC_Q))
      	this->player->moreShild();
    if (mKeyboard->isKeyDown(OIS::KC_E))
    	this->player->moreWapponPower();

    //Naechstes Leben
    if (mKeyboard->isKeyDown(OIS::KC_SPACE) && player->isDead()) {
        this->player->teleport(Vector2(rand()%(SPIELFELDBREITE/2) - SPIELFELDBREITE/4,rand()%(SPIELFELDBREITE/2) - SPIELFELDBREITE/4));
        //this->player->setSpeed(Vector2(rand()%3, rand()%3));
        this->player->awake();
    }
    return true;
}

void UpdateSceneFrameListener::moveMyCamera() {
    switch (CamPosition) {
    case CAMTOPVIEW: {
        int x = this->player->getPosition().x;
        int y = this->player->getPosition().y;
        this->mCamera->setPosition(Vector3(x, y,SPIELEBENE + Zoom));
        this->mCamera->lookAt(Vector3(x,y,SPIELEBENE));
    }
    break;
    case CAMFOLLOW: {
        float x = this->player->getPosition().x;
        float y = this->player->getPosition().y;
        Vector2 locat = player->getSpeed();
        if (!locat.isZeroLength())
            locat.normalise();

        float sX = locat.x * 1500 + Zoom *locat.x/50 ;
        float sY = locat.y * 1500 + Zoom *locat.y/50 ;


       this->mCamera->setPosition(Vector3(x - sX, y - sY,SPIELEBENE + Zoom));
       this->mCamera->lookAt(Vector3(x + sX ,y +sY,SPIELEBENE));
	
	
//         this->mCamera->setPosition(Vector3(SPIELEBENE + Zoom,x - sX, y - sY));
//         this->mCamera->lookAt(Vector3(SPIELEBENE,x + sX ,y +sY));
//        this->mCamera->setNearClipDistance(5);
    }
    break;
    case DYNAMICCAMFOLLOW: {
        float x = this->player->getPosition().x;
        float y = this->player->getPosition().y;
        Vector2 locat = player->getSpeed();

        float sX = locat.x / 550 + Zoom *locat.x/2000 ;
        float sY = locat.y / 550 + Zoom *locat.y/2000 ;

	this->mCamera->setPosition(Vector3(x - sX, y - sY,SPIELEBENE + Zoom));
	this->mCamera->lookAt(Vector3(x + sX ,y +sY,SPIELEBENE));
	
        this->mCamera->setNearClipDistance(5);
    }
    break;
    }

}
