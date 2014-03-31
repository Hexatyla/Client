//
// Menu.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Tue Mar 18 14:19:29 2014 gautier lefebvre
// Last update Sat Mar 22 18:15:36 2014 Gautier Lefebvre
//

#include	"GUIG/Menu.hpp"

GUIG::Menu::Menu():
  AOverlaySceneManager("GUIG_Menu", 25),
  _background(NULL),
  _exit(NULL),
  _back(NULL)
{}

GUIG::Menu::~Menu() {}

void	GUIG::Menu::init(unsigned int wx, unsigned int wy) {
  Ogre::Vector2 winsize(wx, wy);

  this->_background = this->addOverlayImage(winsize, Ogre::Vector2(wx, wy), Ogre::Vector2(_x, _y), "guig_menu_background_img", "black.png", true);
  this->_background->setOpacity(0.7);
  this->_exit = this->addButton(winsize, Ogre::Vector2(89, 101), Ogre::Vector2(_x + 595, _y + 490), "guig_menu_exit_button", "exit.png");
  this->_back = this->addButton(winsize, Ogre::Vector2(89, 101), Ogre::Vector2(_x + 1235, _y + 490), "guig_menu_back_button", "back.png");
  draw();
}

void	GUIG::Menu::draw() {}
