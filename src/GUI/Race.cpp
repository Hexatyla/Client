// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Race.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Race.hpp"

GUI::Race::Race() : AOverlaySceneManager("Race", 10), type(ALEA), run(false)
{
}

GUI::Race::~Race()
{
}

void  GUI::Race::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  alea = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1300, 53),
      "race_setRace_alea",   "choice_race_alea.png");
  alea_hover = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1300, 53),
      "race_setRace_selected_alea",   "choice_race_alea_hover.png");
  r1 = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1350, 53),
      "race_setRace_r1",   "choice_race_r1.png");
  r1_hover = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1350, 53),
      "race_setRace_selected_r1",   "choice_race_r1_hover.png");
  r2 = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1400, 53),
      "race_setRace_r2",   "choice_race_r2.png");
  r2_hover = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1400, 53),
      "race_setRace_selected_r2",   "choice_race_r2_hover.png");
  r3 = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1450, 53),
      "race_setRace_r3",   "choice_race_r3.png");
  r3_hover = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1450, 53),
      "race_setRace_selected_r3",   "choice_race_r3_hover.png");

  r1->changeZOrder(1);
  r1->setVisible(true);
  r1_hover->changeZOrder(0);
  r1_hover->setVisible(false);

  r2->changeZOrder(1);
  r2->setVisible(true);
  r2_hover->changeZOrder(0);
  r2_hover->setVisible(false);

  r3->changeZOrder(1);
  r3->setVisible(true);
  r3_hover->changeZOrder(0);
  r3_hover->setVisible(false);

  alea->changeZOrder(0);
  alea->setVisible(false);
  alea_hover->changeZOrder(1);
  alea_hover->setVisible(true);
  // INIT scene
}

bool  GUI::Race::setType(GUI::TYPE_RACE _act)
{
  if (type != _act)
  {
    type = _act;
    alea->setVisible(true);
    alea_hover->setVisible(false);
    r1->setVisible(true);
    r1_hover->setVisible(false);
    r2->setVisible(true);
    r2_hover->setVisible(false);
    r3->setVisible(true);
    r3_hover->setVisible(false);
    if (type == GUI::ALEA)
    {
      alea->setVisible(false);
      alea_hover->setVisible(true);
    }
    else if (type == GUI::R1)
    {
      r1->setVisible(false);
      r1_hover->setVisible(true);
    }
    else if (type == GUI::R3)
    {
      r3->setVisible(false);
      r3_hover->setVisible(true);
    }
    else if (type == GUI::R2)
    {
      r2->setVisible(false);
      r2_hover->setVisible(true);
    }
    return (true);
  }
  return (false);
}

GUI::TYPE_RACE GUI::Race::getType(void)
{
  return (type);
}

void  GUI::Race::draw()
{
}
