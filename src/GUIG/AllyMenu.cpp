//
// AllyMenu.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Mon Mar 17 14:39:35 2014 gautier lefebvre
// Last update Tue Mar 18 14:51:30 2014 gautier lefebvre
//

#include	"GUIG/AllyMenu.hpp"
#include	"Converter.hpp"

GUIG::AllyMenu::AllyMenu():
  AOverlaySceneManager("GUIG_AllyMenu", 10),
  _winsize(0, 0),
  _background(NULL),
  _team1Text(NULL), _team2Text(NULL),
  _team1(), _team2()
{}

GUIG::AllyMenu::~AllyMenu() {}

void	GUIG::AllyMenu::init(unsigned int wx, unsigned int wy) {
  this->_winsize = Ogre::Vector2(wx, wy);

  this->_background = this->addOverlayImage(this->_winsize, Ogre::Vector2(500, 200), Ogre::Vector2(0 + _x, 0 + _y), "allymenu_background", "black.png", true);

  this->_team1Text = this->addOverlayText(this->_winsize, Ogre::Vector2(0, 0), Ogre::Vector2(100 + _x, 20 + _y), "allymenu_team1_text", "empty.png", "Team 1", true);
  this->_team1Text->setColor(Ogre::ColourValue(0.0, 0.0, 1.0));

  this->_team2Text = this->addOverlayText(this->_winsize, Ogre::Vector2(0, 0), Ogre::Vector2(280 + _x, 20 + _y), "allymenu_team2_text", "empty.png", "Team 2", true);
  this->_team2Text->setColor(Ogre::ColourValue(1.0, 0.0, 0.0));

  // this->addPlayer("kikoolol", 1);
  // this->addPlayer("lolilol", 2);
  // this->addPlayer("pseudo", 1);
  // this->addPlayer("francesca", 2);
  // this->addPlayer("mcfarmer", 1);
}

void	GUIG::AllyMenu::draw() {}

void	GUIG::AllyMenu::clear() {
  for (auto image : this->_team1) {
    this->delOverlay(image->getName());
  }

  for (auto image : this->_team2) {
    this->delOverlay(image->getName());
  }

  this->_team1.clear();
  this->_team2.clear();
}

void	GUIG::AllyMenu::addPlayer(const std::string &nick, int team) {
  switch (team) {
  case (1): {
    OverlayText *text = this->addOverlayText(this->_winsize, Ogre::Vector2(0, 0), Ogre::Vector2(100 + _x, 70 + _y + ((this->_team1.empty() ? 0 : this->_team1.size()) * 25)), "allymenu_team1_" + nick, "empty.png", nick, true);
    this->_team1.push_back(text);
    break;
  }
  case (2): {
    OverlayText *text = this->addOverlayText(this->_winsize, Ogre::Vector2(0, 0), Ogre::Vector2(300 + _x, 70 + _y + ((this->_team2.empty() ? 0 : this->_team2.size()) * 25)), "allymenu_team2_" + nick, "empty.png", nick, true);
    this->_team2.push_back(text);
    break;
  }
  default:
    break;
  }
}
