//
// FadeIn.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:07:16 2014 Yannick Briffa
// Last update Mon Mar 31 12:45:15 2014 geoffrey bauduin
//

#include	"effects/Fade.hh"
#include	"Utils/graphicException.hh"

Fade::Fade(OverlayImage *overlay, double begin, double end, double duration)
  : AFade(overlay, begin, end, duration)
{
  if (begin == end)
    throw graphicException("Invalid value for begin and end in Fade");
}

Fade::~Fade()
{
}

bool		Fade::update(const Ogre::FrameEvent &evt)
{
  if (!_ended)
    {
      _currentDuration += evt.timeSinceLastFrame;
      if (_currentDuration > _duration)
	_ended = true;
      else
	{
	  double a = (_end - _begin) / _duration;
	  _overlay->setOpacity(a * _currentDuration + _begin);
	}
    }
  return true;
}
