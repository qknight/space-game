#include "myoverlays.h"

MyOverlays::MyOverlays(/*OverlayManager *overlayManager*/){
  
  
  OverlayManager& overlayManager = OverlayManager::getSingleton();
  Leben = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelLeben"));
  Leben->setMetricsMode(Ogre::GMM_PIXELS);
  Leben->setPosition(10, 10);
  Leben->setDimensions(500, 10);
  Leben->setMaterialName("Hud/Energie");

  Schild = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelSchild"));
  Schild->setMetricsMode(Ogre::GMM_PIXELS);
  Schild->setPosition(30, 1000);
  Schild->setDimensions(10, 500);
  Schild->setMaterialName("Hud/Energie");
  
  WapponPower = static_cast<OverlayContainer*>(
    overlayManager.createOverlayElement("Panel","PanelWapponPower"));
  WapponPower->setMetricsMode(Ogre::GMM_PIXELS);
  WapponPower->setPosition(50, 1000);
  WapponPower->setDimensions(10, 500);
  WapponPower->setMaterialName("Hud/Energie");
  
  Overlay* overlay = overlayManager.create("OverlayName");
  overlay->add2D(Leben);
  overlay->add2D(Schild);
  overlay->add2D(WapponPower);
  // Show the overlay
  overlay->show();
}
