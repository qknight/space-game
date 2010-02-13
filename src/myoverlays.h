#ifndef MYOVERLAYS_H
#define MYOVERLAYS_H

#include "ExampleFrameListener.h"

class MyOverlays
{
  public:
    MyOverlays(/*OverlayManager *overlayManager*/);
    
    void Aktuallisieren(float leben, float schild, float wapponPoder);
    
  private:
   OverlayContainer* Leben;
   OverlayContainer* Schild;
   OverlayContainer* WapponPower;
   Overlay* overlay;
   Overlay* overlayLeben;
};

#endif // MYOVERLAYS_H
