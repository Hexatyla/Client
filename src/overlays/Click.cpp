//
// Click.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb 10 18:16:30 2014 Yannick Briffa
// Last update Mon Mar  3 12:33:26 2014 Yannick Briffa
//

#include	"overlays/Click.hh"
#include	"overlays/OverlayImage.hh"
#include	"effects/MoveOverlay.hh"
#include	"overlays/Click.hh"
#include	"effects/Scale.hh"

Click::Click()
{
}

Click::~Click()
{
}

IEffect		*Click::effectOnClick()
{
  if (OverlayImage *ptr = dynamic_cast<OverlayImage *>(this))
    {
      if (!ptr->isLocked()) {
	std::pair<double, double>		begin(0.7, 0.7);
	std::pair<double, double>		end(1.0,1.0);

	return (new Scale (ptr, begin, end, 0.3));
      }
      return (NULL);
    }
  return (NULL);
}
