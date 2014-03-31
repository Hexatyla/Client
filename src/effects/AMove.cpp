//
// AMove.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 23:08:45 2014 Yannick Briffa
// Last update Tue Feb 11 09:55:03 2014 Yannick Briffa
//

#include	"effects/AMove.hh"

AMove::AMove(bool repeatable, Ogre::Real speed)
  : AEffect(), ARepeatable(repeatable), _speed(speed), _distance(0)
{
}

AMove::~AMove()
{
}

void		AMove::setSpeed(Ogre::Real speed)
{
  _speed = speed;
}


Ogre::Real	AMove::getSpeed() const
{
  return _speed;
}
