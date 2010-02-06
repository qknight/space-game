#include "ExampleApplication.h"
#include "spacecontroller.h"
#include "spaceview.h"
#include "game.h"

#include "mylogger.h"

class test  {
  public:
  test(){
    modle = new Game();
    view = new SpaceView(modle);
    controller = new SpaceController(view, modle);
  }

  void go(){
    //initialisiert random seed
    srand(111);
    
    controller->GO();
  }
  protected:
    SpaceView *view;
    Game *modle;
    SpaceController *controller;
};


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{
    // Create application object
    test app;

    try {
      mylogger::reset();
      mylogger::logTime();
      mylogger::log("Game Startet");
      app.go();
    } catch( Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
        MessageBox( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
                e.what());
#endif
    }

    return 0;
}