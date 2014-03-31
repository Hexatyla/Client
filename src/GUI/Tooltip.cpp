// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Controller.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "GUI/Tooltip.hpp"

GUI::Tooltip::Tooltip() : AOverlaySceneManager("Tooltip", 10), run(false)
{
}

void  GUI::Tooltip::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  // INIT scene
}

GUI::Tooltip::~Tooltip()
{
}

void GUI::Tooltip::draw()
{
}
