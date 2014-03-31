// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Setting.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Setting.hpp"

GUI::Setting::Setting() : AOverlaySceneManager("Setting", 10), run(false)
{
}

GUI::Setting::~Setting()
{
}

void  GUI::Setting::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  // INIT scene
}

void  GUI::Setting::exit()
{
}

void  GUI::Setting::draw()
{
}
