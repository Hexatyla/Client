// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/GameLoading.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "GUI/GameLoading.hpp"

GUI::GameLoading::GameLoading(const std::string& _name) :  AOverlaySceneManager("GameLoading", 10), me(_name)
{
}

GUI::GameLoading::~GameLoading()
{
}

void  GUI::GameLoading::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  // INIT scene
}

bool  GUI::GameLoading::infoPlayer(const std::string& _name, bool actif, unsigned int equip)
{
  playerToEquip[_name] = equip;
  playerToActif[_name] = actif;
  return (true);
}

bool  GUI::GameLoading::infoPlayer(const std::string& _name, bool actif)
{
  std::map<std::string, unsigned int>::iterator it;

  it = playerToEquip.find(_name);
  if (it == playerToEquip.end())
    return (false);
  playerToActif[_name] = actif;
  return (true);
}

void  GUI::GameLoading::map()
{
}

void  GUI::GameLoading::setMaxElement(unsigned int _max)
{
  maxElement = _max;
}

unsigned int GUI::GameLoading::calc(unsigned int _actElement)
{
  actElement = _actElement;
  if (maxElement == 0)
    return (0);
  pourcent = static_cast<unsigned int>(static_cast<double>(_actElement)
                                         / static_cast<double>(maxElement)
                                         * 100.0);
  return (pourcent);
}

void  GUI::GameLoading::draw()
{
}
