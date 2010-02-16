#include "myoverlays.h"

MyOverlays::MyOverlays(/*OverlayManager *overlayManager*/){
  
  float position = 10;
  OverlayManager &overlayManager = OverlayManager::getSingleton();
  Leben = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelLeben"));
  Leben->setMetricsMode(Ogre::GMM_PIXELS);
  Leben->setPosition(10, position);
  Leben->setDimensions(10, 500);
  Leben->setMaterialName("OverLay/life");

  Schild = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelSchild"));
  Schild->setMetricsMode(Ogre::GMM_PIXELS);
  Schild->setPosition(25, position);
  Schild->setDimensions(10, 500);
  Schild->setMaterialName("OverLay/shild");
  
  WapponPower = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelWapponPower"));
  WapponPower->setMetricsMode(Ogre::GMM_PIXELS);
  WapponPower->setPosition(40, position);
  WapponPower->setDimensions(10, 500);
  WapponPower->setMaterialName("OverLay/wapponpower");
  
  overlay = overlayManager.create("OverlayName");
 // overlayLeben = overlayManager.create("OverlayLeben");
  overlay->add2D(Leben);
  overlay/*Leben*/->add2D(Schild);
  overlay->add2D(WapponPower);
  // Show the overlay
 // overlayLeben->setScale(0.5,0.5);
  overlay->show();
  //overlayLeben->show();
  
 // overlay->setRotate(3);
  
}

void MyOverlays::Aktuallisieren(float leben, float schild, float wapponPoder){
  this->Leben->setHeight(leben);
  Schild->setHeight(schild);
  WapponPower->setHeight(wapponPoder);
//   overlay->setScale(2.0,2.0);
//   overlay->show();
//    Leben->setHeight(300);

}
