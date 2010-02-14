#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <OgreVector2.h>
#include "movableobject.h"

class projectile : public movableObject {
  public:
    projectile( float speedboost, Ogre::Vector2 acceleration, float heaviness);

 //   int getNumber();  
    Ogre::String getObjektName();
    
  protected:
   // int num;
};

#endif // PROJECTILE_H
