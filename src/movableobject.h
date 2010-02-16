#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <OgreVector2.h>
#include <OgreMath.h>
#include <iterator>

#include "notifyable.h"
#include "mylogger.h"

using namespace Ogre;

class movableObject : public notifyable
{
  public:
    movableObject(String ObjectName, float heaviness);
    ~movableObject();
    
    void move(); //bewegt ein Objekt um seine aktuelle Geschwindigkeit
    void accelerate(Vector2 acceleration); //ändert die Geschwindigkeit
    void calculateGravity(movableObject *gravity); //ändert die Geschwindigkeit anhand der Anziehung eines anderen Körpers
    
    double getHeaviness();
    Vector2 getPosition();
    String getObjektName();
    void teleport(Vector2 position);
    Vector2 getSpeed();
    void setSpeed(Vector2 speed);
      
    // gibt den ersten hinzugefuegten SceneNode oder NULL zurueck
    SceneNode* tryGetNode();
    
    //zb fuer geschosse die sich permanent beschleunigen
    Vector2 constAcceleration;
    
    bool circle;
    void setCircleRadius(float r);
  //  float radius;
    float circlespeed;
    float a;
    float b;
    void setGravitationPartner(movableObject *mov);
    
    bool isOutOfArea();
    void moveSlow();
    
    float Damage;
    
    bool dead;
 
  protected:
           
    movableObject * circlePoint;
    
    float phi;
    
    Vector2 position;
    Vector2 speed;
    Vector2 acceleration;
    float heaviness; //Gewicht in tonnen
    String ObjectName;
    private:
    bool moveslow;
};

#endif // MOVABLEOBJECT_H
