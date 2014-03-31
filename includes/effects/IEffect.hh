//
// IMove.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/move
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 22:50:24 2014 Yannick Briffa
// Last update Fri Mar  7 17:33:50 2014 Yannick Briffa
//

#ifndef __IEFFECT_HH__
# define __IEFFECT_HH__

# include	"Ogre.h"

class	IEffect
{
public:
  virtual ~IEffect() {}

  virtual bool	update(const Ogre::FrameEvent &) = 0;

  virtual bool	isEnded() const = 0;

  virtual void	setSpeed(Ogre::Real) = 0;
  virtual Ogre::Real	getSpeed() const = 0;

  virtual void	*getObject() = 0;
};

#endif
