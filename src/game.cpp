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
  //kollisionen();
}

void Game::kollision(movableObject* arg1, movableObject* arg2){
  
//    if (!arg1->isDead() || arg2->isDead()){
  if (arg1->getObjektName() == "Player" && arg2->getObjektName() == "Player"){
    Player *pl1 = (Player*)arg1;
    Player *pl2 = (Player*)arg2;
    if (!pl1->isDead() && !pl2->isDead()){
      pl1->kill();
      pl2->kill();
    }
  } else if (arg1->getObjektName() == "Player"){
    Player *pl1 = (Player*)arg1;
    if (!pl1->isDead()){
      pl1->takeDamage(arg2->Damage);
      if (arg2 ->getObjektName() == "projectile"){
        this->lightObjects.remove(arg2);
        delete arg2;
      }
    }
  } else if (arg2->getObjektName() == "Player"){
    Player *pl1 = (Player*)arg2;
    if (!pl1->isDead()){
      pl1->takeDamage(arg2->Damage);
      if (arg1 ->getObjektName() == "projectile"){
        this->lightObjects.remove(arg1);
        delete arg1;
      }
    }
  } else {
    if (arg1 ->getObjektName() == "projectile"){
      this->lightObjects.remove(arg1);
      delete arg1;
    }
    if (arg2 ->getObjektName() == "projectile"){
      this->lightObjects.remove(arg2);
      delete arg2;
    }
  }
 //   }
}
//bewegt alle schweren Objekte inklusive ihrer gravitation (gravitation wird nur von schweren objekten ausgelöst)
void Game::moveHeavyObjects(){
 // list<movableObject*>::iterator ith;
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
/*
void Game::kollisionen() {  
  list<movableObject*>::iterator it;
  for (it = this->lightObjects.begin(); it != this->lightObjects.end(); ++ it){
    if ((*it)->getPosition().length() < 190){
      movableObject *obj = (*it);
      if (obj->getObjektName() == "Player"){
	obj->kill();
      } else {
	it = this->lightObjects.erase(it);
	delete obj;
      }
    }
  }
}
*/

void Game::removeOutOfAreaObjects(){
  
  list<movableObject*>::iterator it;
  
  for (it = this->lightObjects.begin(); it != this->lightObjects.end(); ++ it){
    if ((*it)->isOutOfArea()){
      if ((*it)->getObjektName() == "Player"){
	//spieler an zufaellige position teleportieren.
        (*it)->teleport(Vector2(rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE,rand()%(2*SPIELFELDBREITE) - SPIELFELDBREITE));
        (*it)->setSpeed(Vector2(rand()%3, rand()%3));
//	cout << "Objekt Teleportiert" << endl;
      } else {
        //objekt entfernen.
        movableObject *obj = (*it);
        it = this->lightObjects.erase(it);
        delete obj;
//	cout << "Objekt entfernt" << endl;
      }
    }
  }
}