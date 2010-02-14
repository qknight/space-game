#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <list>
#include <stack>

#include "movableobject.h"
#include "player.h"
#include "metheor.h"

using namespace std;

class Game
{
  public:
    Game();
  
    void addLightObject(movableObject* mobj);
    void addHeavyObject(movableObject* mobj);
    
    //bewegt alle leichten Objekte inklusive ihrer gravitation (gravitation wird nur von schweren objekten ausgelöst)
    void moveLightObjects();
    
    //bewegt alle schweren Objekte inklusive ihrer gravitation (gravitation wird nur von schweren objekten ausgelöst)
    void moveHeavyObjects();
    
    //liefert true wenn ein neu hinzugefügtes Objekt vorhanden ist.
    bool hasNewObject();
    
    //kollisionen
   // void kollisionen();
    
    //Spielfeld verlassen, dann entvernen....
    void removeOutOfAreaObjects();
    
    //precondition: hasNewObject() == true;
    //liefert das nächste neue Object
    //postcondition: make a new node with this object
    movableObject* getNextNewObject();
    
    void kollision(movableObject* arg1, movableObject* arg2);
    
  protected:   
    //Leichte Objekte auf die Gravitation einwirkt
    list<movableObject*> lightObjects;
    
    //Schwere Objekte die Gravitation Verursachen.
    list<movableObject*> heavyObjects;
    
    //Liste aller neu hinzugefügten Objekte die in der Anzeige übernommen werden sollten.
    stack<movableObject*> nearlyAddedObjects;
    
};

#endif // GAME_H
