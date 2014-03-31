//
// AFade.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:20:49 2014 Yannick Briffa
// Last update Fri Mar  7 17:42:14 2014 Yannick Briffa
//

#ifndef	__AFADE_HH__
# define __AFADE_HH__

# include	"effects/AEffect.hh"
# include	"overlays/OverlayImage.hh"

class	AFade : public AEffect
{
protected:
  OverlayImage	*_overlay;
  double	_begin;
  double	_end;
  double	_duration;
  double	_currentDuration;

public:
  AFade(OverlayImage *, double, double, double);
  virtual ~AFade();

  virtual void	setSpeed(Ogre::Real);
  virtual Ogre::Real	getSpeed() const;
  virtual void	*getObject();
};

#endif
