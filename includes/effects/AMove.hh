//
// Amove.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/move
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 22:50:24 2014 Yannick Briffa
// Last update Tue Feb 11 09:53:47 2014 Yannick Briffa
//

#ifndef __AMOVE_HH__
# define __AMOVE_HH__

# include	"effects/AEffect.hh"
# include	"effects/ARepeatable.hh"

class	AMove : public AEffect, public ARepeatable
{
protected:
  Ogre::Real	_speed;
  Ogre::Real	_distance;

private:
  AMove();

public:
  AMove(bool, Ogre::Real);
  virtual ~AMove();

  virtual void	setSpeed(Ogre::Real);
  virtual Ogre::Real	getSpeed() const;
};

#endif
