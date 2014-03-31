//
// DayNight.cpp for pfa in /home/gautier/pfa
// 
// Made by gautier lefebvre
// Login   <gautier@epitech.net>
// 
// Started on  Tue Mar 11 17:13:23 2014 gautier lefebvre
// Last update Wed Mar 26 13:56:14 2014 Gautier Lefebvre
//

#include	"GUIG/DayNight.hpp"

GUIG::DayNight::DayNight():
  AOverlaySceneManager("GUIG_DAYNIGHT", 10),
  _imageDay(NULL),
  _imageNight(NULL),
  _textMenu(NULL),
  _textTeam(NULL),
  _day(true)
{}

GUIG::DayNight::~DayNight() {}

void	GUIG::DayNight::init(unsigned int winX, unsigned int winY) {
  int px = 0, py = 0;
  Ogre::Vector2 winsize(winX, winY);

  this->_imageDay = this->addOverlayImage(winsize, Ogre::Vector2(65, 75), Ogre::Vector2(_x + 150, _y), "day_logo", "sun.png", true);
  this->_imageNight = this->addOverlayImage(winsize, Ogre::Vector2(65, 75), Ogre::Vector2(_x + 150, _y), "night_logo", "moon_icon.png", true);

  this->_textMenu = this->addOverlayText(winsize, Ogre::Vector2(120, 30), Ogre::Vector2(_x, _y + 10), "daynight_menu_text", "annotation_background.png", "Menu (ESC)", true);
  this->_textTeam = this->addOverlayText(winsize, Ogre::Vector2(120, 30), Ogre::Vector2(_x + 245, _y + 10), "daynight_team_text", "annotation_background.png", "Team (TAB)", true);

  this->_textMenu->setPaddingHeight(5);
  this->_textMenu->setPaddingWidth(5);
  this->_textTeam->setPaddingHeight(5);
  this->_textTeam->setPaddingWidth(5);

  draw();
}

void	GUIG::DayNight::draw() {}

void	GUIG::DayNight::setDate(unsigned int h, unsigned int m, unsigned int s) {
  (void)m;
  (void)s;
  if (h > 8 && h < 21) {
    this->_imageDay->setVisible(true);
    this->_imageNight->setVisible(false);
    this->_day = true;
  }
  else {
    this->_imageDay->setVisible(false);
    this->_imageNight->setVisible(true);
    this->_day = false;
  }
  draw();
}

bool	GUIG::DayNight::isDay() const { return (this->_day); }
