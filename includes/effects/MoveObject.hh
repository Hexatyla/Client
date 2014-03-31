//
// MoveObject.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 11:46:24 2014 Yannick Briffa
// Last update Fri Mar  7 17:37:19 2014 Yannick Briffa
//

#ifndef __MOVEOBJECT_HH__
# define __MOVEOBJECT_HH__

# include	"effects/AMove.hh"

class	MoveObject : public AMove
{
protected:
  Ogre::Entity			*_entity;
  Ogre::SceneNode		*_node;
  std::deque<Ogre::Vector3>	_checkpoint;
  Ogre::Vector3			_direction;
  Ogre::Vector3			_destination;

  bool				nextLocation();

private:
  MoveObject();

public:
  MoveObject(bool, Ogre::Entity *, Ogre::SceneNode *, std::deque<Ogre::Vector3> &, Ogre::Real &);
  virtual ~MoveObject();
  virtual bool	update(const Ogre::FrameEvent &);
  virtual void	*getObject();
};

#endif
