//
// FadeIn.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:07:16 2014 Yannick Briffa
// Last update Mon Mar 31 12:45:33 2014 geoffrey bauduin
//

#include	"effects/Scale.hh"
#include	"Utils/graphicException.hh"

Scale::Scale(OverlayImage *overlay, std::pair<double, double> &begin, std::pair<double, double> &end, double duration)
  : AScale(overlay, begin, end, duration)
{
}

Scale::~Scale()
{
}

bool		Scale::update(const Ogre::FrameEvent &evt)
{
  if (!_ended)
    {
      _currentDuration += evt.timeSinceLastFrame;
      if (_currentDuration > _duration)
	_ended = true;
      else
	{
	  Ogre::Vector2		current;

	  current.x = ((_end.x - _begin.x) / _duration) * _currentDuration + _begin.x;
	  current.y = ((_end.y - _begin.y) / _duration) * _currentDuration + _begin.y;
	  _overlay->setSize(current);
	  _overlay->updateSize();

	  current.x = _center.x - current.x / 2;
	  current.y = _center.y - current.y / 2;
	  _overlay->updatePosition(current);
	}
    }
  return true;
}
