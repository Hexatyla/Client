//
// MoveObject.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 11:46:20 2014 Yannick Briffa
// Last update Fri Mar  7 17:40:59 2014 Yannick Briffa
//

#include	"effects/MoveOverlay.hh"

MoveOverlay::MoveOverlay(bool repeatable, AOverlay *overlay, std::deque<Ogre::Vector2> &walklist, Ogre::Real &speed)
  : AMove(repeatable, speed), _overlay(overlay), _checkpoint(walklist), _direction(Ogre::Vector2::ZERO), _destination(Ogre::Vector2::ZERO)
{
  _overlay->setLocked(true);
}

MoveOverlay::~MoveOverlay()
{
  _overlay->setLocked(false);
  _checkpoint.clear();
}

bool		MoveOverlay::nextLocation() {
  if (_checkpoint.empty())
    return false;
  _destination = _checkpoint.front();
  _checkpoint.pop_front();
  if (_repeatable)
    _checkpoint.push_back(_destination);
  _direction = _destination - _overlay->getPos();
  _distance = _direction.normalise();
  return true;
}

bool		MoveOverlay::update(const Ogre::FrameEvent &evt)
{
  if (!_ended)
    {
      if (_direction == Ogre::Vector2::ZERO)
	_ended = !nextLocation();
      else
	{
	  Ogre::Real	move = _speed * evt.timeSinceLastFrame;
	  _distance -= move;
	  if (_distance <= 0.0f)
	    {
	      _overlay->setPos(_destination);
	      _direction = Ogre::Vector2::ZERO;
	      _ended = !nextLocation();
	    }
	  else {
	    _overlay->setPos((_direction * move) + _overlay->getPos());
	    _overlay->refreshPosition();
	  }
	}
    }
  return true;
}

void		*MoveOverlay::getObject()
{
  return _overlay;
}
