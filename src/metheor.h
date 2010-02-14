#ifndef METHEOR_H
#define METHEOR_H
#include "movableobject.h"

class metheor : public movableObject
{
  public:
    metheor();
    bool takeDamege(float dmg);
  protected: 
    float live;
    
};

#endif // METHEOR_H
