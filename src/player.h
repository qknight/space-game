#ifndef PLAYER_H
#define PLAYER_H
#include "movableobject.h"

#include "projectile.h"
#include "konstanten.h"


class Game;

class Player : public movableObject
{
  public:
    Player(Game *game, float heaviness);
    
    bool fireWappon(projectile *obj);
    void reload();
    Ogre::String getObjektName();
//    int getNumber();
    bool BoostAvaible();
  protected:
    bool boost;
    
    static const float MAXENERGY = 66;
    static const float INITIALLIVE = 100;
    static const float INITIALSHILD = 33;
    static const float INITIALWAPPON = 33;
    static const float WAPPONACCELERATION = 2;
    
    float life;
    float shild;
    float wappon;
    
    float boostAvaible;
    
    static const float wapponStartPosition = 10;//die länge die die die Munition vor dem eigenen Schiff startet.
    Game *game;
    int firedWappon;
    
};

#endif // PLAYER_H
