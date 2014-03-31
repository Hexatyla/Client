//
// MoveOverlay.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 11:46:24 2014 Yannick Briffa
// Last update Fri Mar  7 17:37:26 2014 Yannick Briffa
//

#ifndef __MOVEOVERLAY_HH__
# define __MOVEOVERLAY_HH__

# include	"effects/AMove.hh"
# include	"overlays/AOverlay.hh"

class	MoveOverlay : public AMove
{
protected:
  AOverlay			*_overlay;
  std::deque<Ogre::Vector2>	_checkpoint;
  Ogre::Vector2			_direction;
  Ogre::Vector2			_destination;

  bool				nextLocation();

private:
  MoveOverlay();

public:
  MoveOverlay(bool, AOverlay *, std::deque<Ogre::Vector2> &, Ogre::Real &);
  virtual ~MoveOverlay();
  virtual bool	update(const Ogre::FrameEvent &);
  virtual void	*getObject();
};

#endif
