#include "movobjchangednotifier.h"

movObjChangedNotifier::movObjChangedNotifier(SceneNode* node) : Notifier()
{
  this->node = node;
}

void movObjChangedNotifier::notify(class notifyable *obj)
{  
  movableObject* test;
  test = (movableObject*) obj;
  
  node->setPosition(test->getPosition().x, test->getPosition().y, SPIELEBENE);
  
 // mylogger::log("Die Positionsänderung eines Objekts wurde dem Knoten übergeben!");
}

void movObjChangedNotifier::notifyDelet(notifyable* obj)
{
//  mylogger::log("delete :" + node->getName());
  node->getParentSceneNode()->removeAndDestroyChild(node->getName());
  delete this;
}

SceneNode* movObjChangedNotifier::getNode(){
  return this->node;
}
