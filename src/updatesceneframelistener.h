#ifndef UPDATESCENEFRAMELISTENER_H
#define UPDATESCENEFRAMELISTENER_H
#include "ExampleApplication.h"
#include "Ogre.h"
#include "game.h"
#include "projectile.h"
#include "player.h"
#include "movobjchangednotifier.h"
#include "OgreSceneNode.h"
#include "movableobject.h"
using namespace Ogre;

class UpdateSceneFrameListener : public ExampleFrameListener
{
public:
    UpdateSceneFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr, Game *modle);

    // Overriding the default processUnbufferedKeyInput so the key updates we define
    // later on work as intended.
    bool processUnbufferedKeyInput(const FrameEvent& evt);

    // Overriding the default processUnbufferedMouseInput so the Mouse updates we define
    // later on work as intended.
    bool processUnbufferedMouseInput(const FrameEvent& evt);

    bool frameStarted(const FrameEvent &evt);
    void moveMyCamera();
    void Kolisionen();

protected:
    Game *game;
    Player *player;

    SceneManager *mSceneMgr;   // The current SceneManager
    SceneNode *mCamNode;   // The SceneNode the camera is currently attached to

    bool KeyInput();

    int NodesNum;

    void getNewObjects();
    
    //Verschiedene Kammerapositionen.
    static const int CAMTOPVIEW = 0;
    static const int CAMFOLLOW = 1;
    int CamPosition;
    
    float Zoom;
    
    // kollisionen
    IntersectionSceneQuery* intersectionQuery;
};

#endif // UPDATESCENEFRAMELISTENER_H


