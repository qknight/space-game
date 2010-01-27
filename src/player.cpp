#include "player.h"
#include "game.h"

bool Player::fireWappon(projectile* obj)
{
  if(firedWappon < 1){
    firedWappon =WAPPONREALOADTIME;
    obj->setSpeed(obj->getSpeed() + this->speed);
    obj->teleport(this->getPosition()/* + obj->getSpeed().normalise()*this->wapponStartPosition*/);   
    this->game->addLightObject(obj);
    return true;
  }
  return false;
}

void Player::reload()
{
  firedWappon--;
}

Player::Player(Game *game,float heaviness):movableObject("Player", heaviness)
{
  this->game = game;
  
  life = INITIALLIVE;
  shild = INITIALSHILD;
  wappon = INITIALWAPPON;
  
  firedWappon = 0;
  //num++;
}

Ogre::String Player::getObjektName()
{
  return "Player";
}
/*

int Player::getNumber()
{
  return num;
}
*/

