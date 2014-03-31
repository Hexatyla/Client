//
// AOverlaySceneManager.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:07 2014 Yannick Briffa
// Last update Thu Feb 20 14:59:05 2014 Yannick Briffa
//

#include	"overlays/MainMenuOverlaySceneManager.hh"
#include	"utils/graphicException.hh"
#include	"overlays/OverlayImage.hh"
#include	"overlays/OverlayText.hh"
#include	"overlays/TextBox.hh"

MainMenuOverlaySceneManager::MainMenuOverlaySceneManager()
  : AOverlaySceneManager("MainMenu", 10)
{
}

MainMenuOverlaySceneManager::~MainMenuOverlaySceneManager()
{
}

void			  MainMenuOverlaySceneManager::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2	winsize(winX, winY);

  this->addInputText(winsize, Ogre::Vector2(400, 400), Ogre::Vector2(1070, 250), "imageMenu1", "imageMenu1.png", "Bonjour", true);
  this->addButton(winsize, Ogre::Vector2(300, 300), Ogre::Vector2(660, 400), "ButtonPlay", "ButtonPlay.png");
  this->addButton(winsize, Ogre::Vector2(150, 150), Ogre::Vector2(890, 310), "ButtonOnline", "ButtonOnline.png");
  this->addButton(winsize, Ogre::Vector2(60, 60), Ogre::Vector2(600, 625), "ButtonParameter", "ButtonParameter.png");
  this->addOverlayImage(winsize, Ogre::Vector2(80, 80), Ogre::Vector2(975, 450), "imageMenu2", "imageMenu2.png", true);
  this->addButton(winsize, Ogre::Vector2(150, 150), Ogre::Vector2(970, 545), "ButtonCampagne", "ButtonCampagne.png");
  this->addOverlayImage(winsize, Ogre::Vector2(300, 300), Ogre::Vector2(780, 650), "imageMenu3", "imageMenu3.png", true);
  this->addOverlayImage(winsize, Ogre::Vector2(110, 110), Ogre::Vector2(645, 660), "imageMenu4", "imageMenu4.png", true);
  this->addOverlayImage(winsize, Ogre::Vector2(220, 220), Ogre::Vector2(430, 425), "imageMenu5", "imageMenu5.png", true);
  this->addOverlayImage(winsize, Ogre::Vector2(260, 260), Ogre::Vector2(525, 210), "imageMenu6", "imageMenu6.png", true);
  this->addOverlayImage(winsize, Ogre::Vector2(90, 90), Ogre::Vector2(790, 300), "imageMenu7", "imageMenu7.png", true);
  this->addOverlayImage(winsize, Ogre::Vector2(winX, winY), Ogre::Vector2(0, 0), "black", "black.png");

  TextBox	*ptr = new TextBox(_name, "TestTextBox", "redBorder.png", _priority, true);

  ptr->init("cyanBorder.png");
  ptr->setVisible(true);
  ptr->setSize(Ogre::Vector2(500, 500));
  ptr->setWindowDimensions(winsize);
  ptr->updatePosition(Ogre::Vector2(50, 50));
  ptr->setBorders(Ogre::Vector2(5,20));
  ptr->setFont("MyFont");
  ptr->setMaxLine(20);
  ptr->setWidthLine(5);

  insertOverlay(ptr->getName(), ptr);


  OverlayImage	*tmp = dynamic_cast<OverlayImage *>(getOverlay("black"));

  tmp->setOpacity(0.3);
  tmp->changeZOrder(1);
}
