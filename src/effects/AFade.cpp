//
// AFade.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:37:36 2014 Yannick Briffa
// Last update Fri Mar  7 17:39:08 2014 Yannick Briffa
//

#include	"effects/AFade.hh"

AFade::AFade(OverlayImage *overlay, double begin, double end, double duration)
  : _overlay(overlay), _begin(begin), _end(end), _duration(duration), _currentDuration(0)
{
}

AFade::~AFade()
{
}

void		AFade::setSpeed(Ogre::Real speed)
{
  _duration = speed;
}

Ogre::Real	AFade::getSpeed() const
{
  return (_duration);
}

void		*AFade::getObject()
{
  return _overlay;
}
