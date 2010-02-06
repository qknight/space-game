#ifndef MOVOBJCHANGEDNOTIFIER_H
#define MOVOBJCHANGEDNOTIFIER_H

#include <OgreSceneNode.h>

#include "notifyable.h"
#include "movableobject.h"
#include "notifier.h"
#include "mylogger.h"
#include "konstanten.h"

using namespace Ogre;
class notifyable;

class movObjChangedNotifier : public Notifier
{
  public:
    movObjChangedNotifier(SceneNode* node, SceneManager *scMr);
    //precondition: notifyable is from class movableObject
    void notify(notifyable* obj);
    void notifyDelet(notifyable* obj);
//     test movableObject;
    SceneNode* getNode();
  protected:
    SceneNode *node;
    SceneManager* scMr;
};

#endif // MOVOBJCHANGEDNOTIFIER_H
