#include "myoverlays.h"

MyOverlays::MyOverlays(/*OverlayManager *overlayManager*/){
  
  float position = 770;
  OverlayManager &overlayManager = OverlayManager::getSingleton();
  Leben = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelLeben"));
  Leben->setMetricsMode(Ogre::GMM_PIXELS);
  Leben->setPosition(10, position);
  Leben->setDimensions(10, 500);
  Leben->setMaterialName("space-game/myMoon");

   OverlayContainer* Schild = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelSchild"));
  Schild->setMetricsMode(Ogre::GMM_PIXELS);
  Schild->setPosition(25, position);
  Schild->setDimensions(10, 500);
  Schild->setMaterialName("space-game/myMoon");
  
   OverlayContainer* WapponPower = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelWapponPower"));
  WapponPower->setMetricsMode(Ogre::GMM_PIXELS);
  WapponPower->setPosition(40, position);
  WapponPower->setDimensions(10, 500);
  WapponPower->setMaterialName("space-game/myMoon");
  
  overlay = overlayManager.create("OverlayName");
  overlay->add2D(Leben);
  overlay->add2D(Schild);
  overlay->add2D(WapponPower);
  // Show the overlay
  overlay->setScale(1,1);
  overlay->show();
  
 // overlay->setRotate(3);
  
}

void MyOverlays::Aktuallisieren(float leben, float schild, float wapponPoder){
//   this->Leben->setWidth(leben);
//   Schild->setWidth(schild);
//   WapponPower->setWidth(wapponPoder);
//   overlay->setScale(2.0,2.0);
//   overlay->show();

}
