//
// Ressource.cpp for pfa in /home/gautier/pfa
// 
// Made by gautier lefebvre
// Login   <gautier@epitech.net>
// 
// Started on  Tue Mar 11 13:51:59 2014 gautier lefebvre
// Last update Mon Mar 24 19:23:28 2014 geoffrey bauduin
//

#include	"GUIG/Ressource.hpp"
#include	"Converter.hpp"

GUIG::Ressource::Ressource():
  AOverlaySceneManager("GUIG_Ressource", 10),
  _gold(0),
  _wood(0),
  _food(0),
  _maxfood(0),
  _race(Race::RANDOM),
  _race1Logo(NULL),
  _race2Logo(NULL),
  _race3Logo(NULL),
  _woodLogo(NULL),
  _goldLogo(NULL),
  _foodText(NULL),
  _woodText(NULL),
  _goldText(NULL)
{}

GUIG::Ressource::~Ressource() {}

void		GUIG::Ressource::init(unsigned int winX, unsigned int winY) {
  int px = 0;
  int py = 0;
  Ogre::Vector2	winsize(winX, winY);

  this->_race1Logo = this->addOverlayImage(winsize, Ogre::Vector2(89, 101), Ogre::Vector2(36 + _x, 32 + _y), "ressources_race1_logo", "race_1.png", true);
  this->_race2Logo = this->addOverlayImage(winsize, Ogre::Vector2(89, 101), Ogre::Vector2(36 + _x, 32 + _y), "ressources_race2_logo", "race_2.png", true);
  this->_race3Logo = this->addOverlayImage(winsize, Ogre::Vector2(89, 101), Ogre::Vector2(36 + _x, 32 + _y), "ressources_race3_logo", "race_3.png", true);

  this->_woodLogo = this->addOverlayImage(winsize, Ogre::Vector2(26, 30), Ogre::Vector2(115 + _x, 25 + _y), "ressources_wood_logo", "wood_icon.png", true);
  this->_goldLogo = this->addOverlayImage(winsize, Ogre::Vector2(26, 30), Ogre::Vector2(129 + _x, 52 + _y), "ressources_gold_logo", "gold_icon.png", true);

  this->_foodText = this->addOverlayText(winsize, Ogre::Vector2(89, 24), Ogre::Vector2(36 + _x, 68 + _y), "ressources_food_text", "bg_black_transparent.png", "  3/4", false);
  this->_foodText->setColor(Ogre::ColourValue(1.0f, 51.0 / 255.0, 51.0 / 255.0));
  this->_woodText = this->addOverlayText(winsize, Ogre::Vector2(100, 100), Ogre::Vector2(147 + _x, 25 + _y), "ressources_wood_text", "empty.png", "0", false);
  this->_goldText = this->addOverlayText(winsize, Ogre::Vector2(100, 100), Ogre::Vector2(162 + _x, 55 + _y), "ressources_gold_text", "empty.png", "0", false);

  this->_woodText->setColor(Ogre::ColourValue(0, 1, 0));
  this->_goldText->setColor(Ogre::ColourValue(1, 1, 0));

  setRace(Race::GENICIA);
  draw();
}

void		GUIG::Ressource::draw() {}

void		GUIG::Ressource::setGold(unsigned int g) {
  this->_gold = g;
  this->_goldText->setText(StringOfUInt(g));
  draw();
}

void		GUIG::Ressource::setWood(unsigned int w) {
  this->_wood = w;
  this->_woodText->setText(StringOfUInt(w));
  draw();
}

void		GUIG::Ressource::setFood(unsigned int f) {
  this->_food = f;
  this->_foodText->setText("  " + StringOfUInt(this->_food) + "/" + StringOfUInt(this->_maxfood));
  draw();
}

void		GUIG::Ressource::setMaxFood(unsigned int mf) {
  this->_maxfood = mf;
  this->_foodText->setText("  "  + StringOfUInt(this->_food) + "/" + StringOfUInt(this->_maxfood));
  draw();
}

void		GUIG::Ressource::setRace(Race::Race r) {
  this->_race = r;
  switch (this->_race) {
  case (Race::GENICIA):
    this->_race1Logo->setVisible(true);
    this->_race2Logo->setVisible(false);
    this->_race3Logo->setVisible(false);
    break ;

  case (Race::HUMANOIDE):
    this->_race1Logo->setVisible(false);
    this->_race2Logo->setVisible(true);
    this->_race3Logo->setVisible(false);
    break ;

  case (Race::IMPERIUM):
    this->_race1Logo->setVisible(false);
    this->_race2Logo->setVisible(false);
    this->_race3Logo->setVisible(true);
    break ;

  default:
    break;
  }
  draw();
}
