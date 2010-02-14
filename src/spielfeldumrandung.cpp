#include "spielfeldumrandung.h"
Spielfeldumrandung::Spielfeldumrandung(SceneManager* mSceneMgr){
  
    ManualObject* endOfUniverse =  mSceneMgr->createManualObject("endOfUniverse"); 
    SceneNode* endOfUniverseNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("endOfUniverse_node"); 
    
    MaterialPtr endOfUniverseMaterial = MaterialManager::getSingleton().create("endOfUniverseMaterial","debugger"); 
    endOfUniverseMaterial->setReceiveShadows(false); 
    endOfUniverseMaterial->getTechnique(0)->setLightingEnabled(true); 
    endOfUniverseMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0); 
    endOfUniverseMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0); 
    endOfUniverseMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,0,0); 
    
    endOfUniverse->begin("endOfUniverseMaterial", Ogre::RenderOperation::OT_LINE_STRIP); 
    endOfUniverse->position(SPIELFELDBREITE, SPIELFELDBREITE, SPIELEBENE); 
    endOfUniverse->position(-1*SPIELFELDBREITE, SPIELFELDBREITE, SPIELEBENE); 
    endOfUniverse->position(-1*SPIELFELDBREITE, -1*SPIELFELDBREITE, SPIELEBENE); 
    endOfUniverse->position(SPIELFELDBREITE, -1*SPIELFELDBREITE, SPIELEBENE); 
    endOfUniverse->position(SPIELFELDBREITE, SPIELFELDBREITE, SPIELEBENE); 
    endOfUniverse->end(); 
    
    endOfUniverse->setQueryFlags(100);
    endOfUniverseNode->attachObject(endOfUniverse);
    
    ManualObject* nearlyEndOfUniverse =  mSceneMgr->createManualObject("nearlyEndOfUniverse"); 
    SceneNode* nearlyEndOfUniverseNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("nearlyEndOfUniverse_node"); 
    
    MaterialPtr nearlyEndOfUniverseMaterial = MaterialManager::getSingleton().create("nearlyEndOfUniverseMaterial","debugger"); 
    nearlyEndOfUniverseMaterial->setReceiveShadows(false); 
    nearlyEndOfUniverseMaterial->getTechnique(0)->setLightingEnabled(true); 
    nearlyEndOfUniverseMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,0,0); 
    nearlyEndOfUniverseMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,0); 
    nearlyEndOfUniverseMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,0); 
    const int abstand = 10500;
    nearlyEndOfUniverse->begin("nearlyEndOfUniverseMaterial", Ogre::RenderOperation::OT_LINE_STRIP); 
    nearlyEndOfUniverse->position((SPIELFELDBREITE -abstand), (SPIELFELDBREITE -abstand), SPIELEBENE); 
    nearlyEndOfUniverse->position(-1*(SPIELFELDBREITE -abstand), (SPIELFELDBREITE -abstand), SPIELEBENE); 
    nearlyEndOfUniverse->position(-1*(SPIELFELDBREITE -abstand), -1*(SPIELFELDBREITE -abstand), SPIELEBENE); 
    nearlyEndOfUniverse->position((SPIELFELDBREITE -abstand), -1*(SPIELFELDBREITE -abstand), SPIELEBENE); 
    nearlyEndOfUniverse->position((SPIELFELDBREITE -abstand), (SPIELFELDBREITE -abstand), SPIELEBENE); 
    // etc 
    nearlyEndOfUniverse->end(); 
    nearlyEndOfUniverse->setQueryFlags(100);
    nearlyEndOfUniverseNode->attachObject(nearlyEndOfUniverse); 
}