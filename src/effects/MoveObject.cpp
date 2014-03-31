//
// MoveObject.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 11:46:20 2014 Yannick Briffa
// Last update Fri Mar  7 17:40:11 2014 Yannick Briffa
//

#include	"effects/MoveObject.hh"

MoveObject::MoveObject(bool repeatable, Ogre::Entity *entity, Ogre::SceneNode *node, std::deque<Ogre::Vector3> &walklist, Ogre::Real &speed)
  : AMove(repeatable, speed), _entity(entity), _node(node), _checkpoint(walklist), _direction(Ogre::Vector3::ZERO), _destination(Ogre::Vector3::ZERO)
{
}

MoveObject::~MoveObject()
{
  _checkpoint.clear();
}

bool		MoveObject::nextLocation() {
  if (_checkpoint.empty())
    return false;
  _destination = _checkpoint.front();
  _checkpoint.pop_front();
  if (_repeatable)
    _checkpoint.push_back(_destination);
  _direction = _destination - _node->getPosition();
  _distance = _direction.normalise();
  return true;
}

bool		MoveObject::update(const Ogre::FrameEvent &evt)
{
  if (!_ended)
    {
      if (_direction == Ogre::Vector3::ZERO)
	_ended = !nextLocation();
      else
	{
	  Ogre::Real	move = _speed * evt.timeSinceLastFrame;
	  _distance -= move;
	  if (_distance <= 0.0f)
	    {
	      _node->setPosition(_destination);
	      _direction = Ogre::Vector3::ZERO;
	      _ended = !nextLocation();
	    }
	  else
	    _node->translate(_direction * move);
	}
    }
  return true;
}

void		*MoveObject::getObject()
{
  return _entity;
}
