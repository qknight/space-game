#ifndef SPACECONTROLLER_H
#define SPACECONTROLLER_H
#include "spaceview.h"
#include "game.h"

class SpaceController
{
  public:
    SpaceController(SpaceView *view, Game* modle);
    //start loop
    void GO();
  private:
    SpaceView *view;
    Game *modle;
};

#endif // CONTROLLER_H
