#include "spacecontroller.h"


SpaceController::SpaceController(SpaceView *view, Game *model)
{
  this->modle = model;
  this->view = view;
}

void SpaceController::GO()
{  
  this->view->go();
}



