#include "metheor.h"
#include "konstanten.h"
metheor::metheor():movableObject("metheor",1+rand()%100){
  this->live = 1+rand()%(rand()%200);
  
  //zufaellige possition am spielfeldrand.
  if (rand()%2){
    if (rand()%2){
      this->position.x = SPIELFELDBREITE-100;  
    }else {
      this->position.x = -1 * SPIELFELDBREITE+100;
    }
    this->position.y = (rand()% (2*SPIELFELDBREITE))-SPIELFELDBREITE;
  } else {
    if (rand()%2){
      this->position.y = SPIELFELDBREITE-100;  
    }else {
      this->position.y = -1 * SPIELFELDBREITE+100;
    }
    this->position.x = (rand()% (2*SPIELFELDBREITE))-SPIELFELDBREITE;
  }
  Vector2 posnorm = this->position.normalisedCopy();
  posnorm.x = -1.0*posnorm.x* (rand()%100);
  posnorm.y = -1.0*posnorm.y* (rand()%100);
  this->accelerate(posnorm);
  
  posnorm = this->position.normalisedCopy();
  posnorm.x = -1.0*posnorm.x* (rand()%10);
  posnorm.y = -1.0*posnorm.y* (rand()%10);
  this->constAcceleration = posnorm;
}
bool metheor::takeDamege(float dmg){
  this->live -= dmg;
  return this->live <= 0;
}