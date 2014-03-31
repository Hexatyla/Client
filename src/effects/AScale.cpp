//
// AFade.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:37:36 2014 Yannick Briffa
// Last update Fri Mar  7 17:39:35 2014 Yannick Briffa
//

#include	"effects/AScale.hh"

AScale::AScale(OverlayImage *overlay, std::pair<double, double> &begin, std::pair<double, double> &end, double duration)
  : _overlay(overlay), _duration(duration), _currentDuration(0), _real(overlay->getSize())
{
  overlay->setLocked(true);
  _begin.x = _real.x * begin.first;
  _begin.y = _real.y * begin.second;

  _end.x = _real.x * end.first;
  _end.y = _real.y * end.second;

  _center.x = overlay->getPosInWindow().x + _real.x / 2;
  _center.y = overlay->getPosInWindow().y + _real.y / 2;
}

AScale::~AScale()
{
  _overlay->setLocked(false);
}

void		AScale::setSpeed(Ogre::Real speed)
{
  _duration = speed;
}

Ogre::Real	AScale::getSpeed() const
{
  return (_duration);
}

void		*AScale::getObject()
{
  return _overlay;
}
