#include "game.h"
#include "mylogger.h"

Game::Game(){
 //this->lightObjects->add(mew movableObject);

 //lightObjects = new list<movableObject*>();
 //heavyObjects = new list<movableObject*>();
 //nearlyAddedObjects = new stack<movableObject*>();
}
void Game::addLightObject(movableObject *mobj){
    this->lightObjects.push_back(mobj);
    this->nearlyAddedObjects.push(mobj);
 //   mylogger::log(mobj->getObjektName() + " wurde als Leichtes Objekt zum Modle hinzugefügt");
}

void Game::addHeavyObject(movableObject *mobj){
    this->heavyObjects.push_back(mobj);
    this->nearlyAddedObjects.push(mobj);
}
        
//liefert true wenn ein neu hinzugefügtes Objekt vorhanden ist.
bool Game::hasNewObject(){
    return not this->nearlyAddedObjects.empty();
}

//precondition: hasNewObject() == true;
//liefert das nächste neue Object
//postcondition: make a new node with this object
movableObject* Game::getNextNewObject(){
    movableObject* ret = nearlyAddedObjects.top();
    nearlyAddedObjects.pop();
    
    return ret;
}

//bewegt alle leichten Objekte inklusive ihrer gravitation (gravitation wird nur von schweren objekten ausgelöst)
void Game::moveLightObjects(){
  list<movableObject*>::iterator ith;
  list<movableObject*>::iterator itl;
  
  //Die Gravitation berechnen 
  for (ith = this->heavyObjects.begin();ith != this->heavyObjects.end(); ++ith){
    for (itl = this->lightObjects.begin();itl != this->lightObjects.end(); ++itl){
      (*itl)->calculateGravity((*ith));
    }
  }

  //Das Bewegen Berechnen
  for (itl = this->lightObjects.begin(); itl != this->lightObjects.end(); ++ itl){
    (*itl)->move();
  //  mylogger::log((*itl)->getObjektName() + " wurde als leichtes Objekt bewegt");
  }
  kollisionen();
}

//bewegt alle schweren Objekte inklusive ihrer gravitation (gravitation wird nur von schweren objekten ausgelöst)
void Game::moveHeavyObjects(){
  list<movableObject*>::iterator ith;
  list<movableObject*>::iterator itl;
  //gravitation berechnen
 /* for (ith = this->heavyObjects.begin();ith != this->heavyObjects.end(); ++ith){
    for (itl = this->heavyObjects.begin();itl != this->heavyObjects.end(); ++itl){
      if (ith != itl){
	(*itl)->calculateGravity((*ith));
      }
    }
  }*/
  
    //Das Bewegen Berechnen
  for (itl = this->heavyObjects.begin(); itl != this->heavyObjects.end(); ++ itl){
    (*itl)->move();
  //  mylogger::log((*itl)->getObjektName() + " wurde als leichtes Objekt bewegt");
  }
  //kollisionen();
}

//TODO Bisher: DUMMYFUNKTION DIE NUR OBJEKTE IM MITTELPUNT ENTFERNT!!
void Game::kollisionen() {  
  list<movableObject*>::iterator it;
  for (it = this->lightObjects.begin(); it != this->lightObjects.end(); ++ it){
    if ((*it)->getPosition().length() < 190){
      movableObject *obj = (*it);
      it = this->lightObjects.erase(it);
      delete obj;
    }
  }
}
