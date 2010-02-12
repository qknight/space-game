#ifndef MYOVERLAYS_H
#define MYOVERLAYS_H

#include "ExampleFrameListener.h"

class MyOverlays
{
  public:
    MyOverlays(/*OverlayManager *overlayManager*/);
    
  private:
   OverlayContainer* Leben;
   OverlayContainer* Schild;
   OverlayContainer* WapponPower;
};

#endif // MYOVERLAYS_H
