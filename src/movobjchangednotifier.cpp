#include "movobjchangednotifier.h"
#include <OgreSceneManager.h>

movObjChangedNotifier::movObjChangedNotifier(SceneNode* node, SceneManager *scMr) : Notifier()
{
  this->node = node;
  this->scMr = scMr;
}

void movObjChangedNotifier::notify(class notifyable *obj)
{  
  movableObject* test;
  test = (movableObject*) obj;
  
  node->setPosition(test->getPosition().x, test->getPosition().y, SPIELEBENE);
//<<<<<<< HEAD:src/movobjchangednotifier.cpp
/*  node->setPosition(SPIELEBENE, test->getPosition().x, test->getPosition().y);*/
//=======
//>>>>>>> 6336111a2e4d1e2ddaf94251995af14005816dba:src/movobjchangednotifier.cpp
 // mylogger::log("Die Positionsänderung eines Objekts wurde dem Knoten übergeben!");
}

void movObjChangedNotifier::notifyDelet(notifyable* obj)
{
//  mylogger::log("delete :" + node->getName());

 // this->scMr->destroyEntity((Entity*)node->getAttachedObjectIterator().getNext());
//   Entity *ent = (Entity*)node->getChild(0);
//   this->node->detachAllObjects();
//   this->scMr->destroyEntity(ent);
  this->scMr->destroySceneNode(node);
//   node->getParentSceneNode()->detachObject(node->getName());
//   node->removeAndDestroyAllChildren();
//   node->detachAllObjects();
//  delete node;
  delete this;
}

SceneNode* movObjChangedNotifier::getNode(){
  return this->node;
}
