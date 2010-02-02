#include "movableobject.h"
#include "movobjchangednotifier.h"



using namespace Ogre;
   
movableObject::movableObject(String ObjectName, float heaviness)
{
  this->ObjectName = ObjectName;
  this->position.x = 0;
  this->position.y = 0;
  this->speed.x= 0;
  this->speed.y = 0;
  this->acceleration.x = 0;
  this->acceleration.y = 0;
  
  this->heaviness = heaviness;
}

movableObject::~movableObject()
{
}

String movableObject::getObjektName()
{
  return ObjectName;
}

//berechnet die aktuelle geschwindigkeit aus der vorherigen geschwindigkeit
//berechnet die Neue Position anhand der geschwindigkeit
void movableObject::move(){
  speed += acceleration;
  position += speed; 
  
  accelerate(new Vector2(0,0));
//  mylogger::log("Object " + this->getObjektName() + " moved");
  notifyable::notify();
}

//ändert die Geschwindigkeit
void movableObject::accelerate(Vector2 *acceleration){
  this->acceleration.x = acceleration->x;
  this->acceleration.y = acceleration->y;
//  mylogger::log(this->getObjektName() + " beschleunigt");
}

//ändert die Geschwindigkeit anhand der Anziehung eines anderen Körpers
void movableObject::calculateGravity(movableObject *gravity){
  //Gravitationskonstante in der Realität ist sie 6,67428*10^-11
  //da hier in tonnen gerechnet wird nur 10^-9
  const double G = 0.000000067428;
  
  //abstand der beiden Körper im quadrat
  double r = (position.x - gravity->getPosition().x)*(position.x - gravity->getPosition().x) +
	     (position.y - gravity->getPosition().y)*(position.y - gravity->getPosition().y);
  
  //die Kraft die auf die Körper einwirkt.
  double dF = (G * gravity->getHeaviness() * this->heaviness)/r;
  //die Richtung der Kraft als Vector
  Vector2 vF = gravity->position - this->position;
  //Die kraft bekommt die richtige länge
  if (vF.isZeroLength()){
    
  }else{
    double l = dF/vF.length();
    vF.x *= l;
    vF.y *= l;
    
    //die Beschleunigung die dieses Objekt erfährt
    Vector2 a = vF / this->heaviness;
    
    //beschleunigt das Objekt.
    this->speed += a;
  }  
/*
//der selbe code nur dass die eigene Masse herrausgekürtzt wurde.
//abstand der beiden Körper im quadrat
  double r = pow(position.x - gravity->getPosition().x,2) +
	      pow(position.y - gravity->getPosition().y,2);
  
  //die Richtung der Kraft als Vector
  Vector2 vF = gravity->position - this->position;
  //Die kraft bekommt die richtige länge
  double l = ((G * gravity->getHeaviness())/r)/vF.length();
  vF.x *= l;
  vF.y *= l;
  //die Beschleunigung die dieses Objekt erfährt
  Vector2 a = vF ;
  
  //beschleunigt das Objekt.
  this->speed += a;*/
}


double movableObject::getHeaviness(){
  return heaviness;
}
Vector2 movableObject::getPosition(){
  return position;
}
    
void movableObject::teleport(Vector2 position)
{
  this->position = position;
  notifyable::notify();
}

Vector2 movableObject::getSpeed()
{
  return this->speed;
}

void movableObject::setSpeed(Vector2 speed)
{
  this->speed = speed;
}

SceneNode* movableObject::tryGetNode(){
  std::list<movObjChangedNotifier*>::iterator it;
  for (it = this->mustBeNotified.begin(); it != this->mustBeNotified.end(); ++it){
    SceneNode* node =(*it)->getNode();
    if (node != NULL){
      return node;
    }
  }
  return NULL;
}





    