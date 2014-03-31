// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Controller.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "overlays/MainHexatyla.hpp"
#include  "utils/graphicException.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"

MainHexatyla::MainHexatyla() : AOverlaySceneManager("MainMenu", 10)
{
}

MainHexatyla::~MainHexatyla()
{
}

void  MainHexatyla::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  this->addButton(winsize,        Ogre::Vector2(300, 300), Ogre::Vector2(660, 400), "ButtonPlay");
  this->addButton(winsize,        Ogre::Vector2(150, 150), Ogre::Vector2(890, 310), "ButtonOnline");
  this->addButton(winsize,        Ogre::Vector2(60, 60), Ogre::Vector2(600, 625), "ButtonParameter");
  this->addOverlayImage(winsize,  Ogre::Vector2(80, 80), Ogre::Vector2(975, 450), "imageMenu2", true);
  this->addButton(winsize,        Ogre::Vector2(150, 150), Ogre::Vector2(970, 545), "ButtonCampagne");
  this->addOverlayImage(winsize,  Ogre::Vector2(300, 300), Ogre::Vector2(780, 650), "imageMenu3", true);
  this->addOverlayImage(winsize,  Ogre::Vector2(110, 110), Ogre::Vector2(645, 660), "imageMenu4", true);
  this->addOverlayImage(winsize,  Ogre::Vector2(220, 220), Ogre::Vector2(430, 425), "imageMenu5", true);
  this->addOverlayImage(winsize,  Ogre::Vector2(260, 260), Ogre::Vector2(525, 210), "imageMenu6", true);
  this->addOverlayImage(winsize,  Ogre::Vector2(90, 90), Ogre::Vector2(790, 300), "imageMenu7", true);
  this->addOverlayImage(winsize,  Ogre::Vector2(winX, winY), Ogre::Vector2(0, 0), "black");

  OverlayImage  *tmp = dynamic_cast<OverlayImage *>(getOverlay("black"));
  tmp->setOpacity(0.3);
  tmp->changeZOrder(1);
}
