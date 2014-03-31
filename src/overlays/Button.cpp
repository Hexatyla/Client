//
// Button.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sun Feb  9 22:22:44 2014 Yannick Briffa
// Last update Wed Feb 12 16:07:15 2014 Yannick Briffa
//

#include	"overlays/Button.hh"

Button::Button(std::string const &scene, std::string const &name, std::string const &file, ushort priority, bool locked)
  : OverlayImage(scene, name, file, priority, locked)
{
}

Button::~Button()
{
  this->setVisible(false);
}
