#include "projectile.h"


projectile::projectile(float speedboost, Ogre::Vector2 acceleration, float heaviness) : 
           movableObject("projectile", heaviness) {
  num++;
/*  this->acceleration = acceleration;
  acceleration.normalise();
  acceleration *= speedboost;
  this->accelerate(&acceleration);
  */
  
  this->speed += acceleration;
  acceleration.normalise();
  acceleration *= speedboost;
  this->speed += acceleration;
  
  this->ObjectName = "projectile";
}
/*
static Ogre::String projectile::getObjektName(){
  return "projectile";
}*/



int projectile::getNumber()
{
  return num;
}
