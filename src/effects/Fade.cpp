//
// FadeIn.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:07:16 2014 Yannick Briffa
// Last update Wed Feb 12 15:59:10 2014 Yannick Briffa
//

#include	"effects/Fade.hh"
#include	"utils/graphicException.hh"

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
