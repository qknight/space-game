#include "player.h"
#include "game.h"

bool Player::fireWappon(projectile* obj)
{
  if(firedWappon < 1 && !this->isDead()){
    firedWappon = WAPPONREALOADTIME;
    obj->setSpeed(obj->getSpeed() + this->speed);
    obj->teleport(this->getPosition() + obj->getSpeed().normalisedCopy()*this->wapponStartPosition);   
    this->game->addLightObject(obj);
    return true;
  }
  return false;
}

void Player::reload()
{
  firedWappon--;
  if (boostAvaible < SPEEDBOOST)
    boostAvaible += 0.02;
  if (boostAvaible >= SPEEDBOOST)
    this->boost = true;
}
bool Player::BoostAvaible()
{
  if (this->boostAvaible > 1 && boost){
      boostAvaible--;
      return true;
  }
  boost = false;
  return false;  
}
Player::Player(Game *game,float heaviness):movableObject("Player", heaviness)
{
  this->game = game;
  
  life = INITIALLIVE;
  shild = INITIALSHILD;
  wappon = INITIALWAPPON;
  
  firedWappon = 0;
  boost = true;
  boostAvaible = SPEEDBOOST;
  
//  wapponStartPosition = 50;
  
  this->ObjectName = "Player";
  //num++;
}

void Player::takeDamage(int arg1){
    this->shild -= arg1;
  //cout  <<"s: " << shild << endl;
    if (shild < 0){
      
	this->life += shild;
	shild = 0;
	//cout <<"l: "<< life << endl;
	if (this->life <=0){
	  this->kill();
	  
	}
    }
}

void Player::move(){
  if(!dead)
    movableObject::move();
}

void Player::kill(){
    dead = true;
    this->speed = 0;
    this->acceleration = 0;
    //cout << "KILL!!!";
}
 bool Player::isDead(){
    return dead;
}
void Player::awake(){
    dead = false;  
  life = INITIALLIVE;
  shild = INITIALSHILD;
  wappon = INITIALWAPPON;
  this->speed = 0;
}
/* 
int Player::getNumber()
{
  return num;
}
*/

