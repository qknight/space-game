#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include "ExampleApplication.h"
#include "updatesceneframelistener.h"

class SpaceView : public ExampleApplication
{
  public:
    SpaceView(Game* modle);
    ~SpaceView();
  protected:
    void createScene(void);
    void createCamera(void);
    void createFrameListener(void);
    
    Game *modle;
};   


#endif