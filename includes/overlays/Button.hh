//
// Button.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sun Feb  9 22:22:47 2014 Yannick Briffa
// Last update Wed Feb 12 16:06:06 2014 Yannick Briffa
//

#ifndef __BUTTON_HH__
# define __BUTTON_HH__

# include	"overlays/OverlayImage.hh"
# include	"overlays/Click.hh"

class	Button : public OverlayImage, public Click
{
public:
  Button(std::string const &scene, std::string const &name, std::string const &file, ushort prio, bool locked = false);
  virtual ~Button();
};

#endif
