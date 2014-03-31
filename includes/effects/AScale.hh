//
// AFade.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:20:49 2014 Yannick Briffa
// Last update Fri Mar  7 17:36:41 2014 Yannick Briffa
//

#ifndef	__ASCALE_HH__
# define __ASCALE_HH__

# include	"overlays/OverlayImage.hh"
# include	"effects/AEffect.hh"

class	AScale : public AEffect
{
protected:
  OverlayImage			*_overlay;
  double			_duration;
  double			_currentDuration;
  Ogre::Vector2			_real;
  Ogre::Vector2			_begin;
  Ogre::Vector2			_end;
  Ogre::Vector2			_center;

public:
  AScale(OverlayImage *, std::pair<double, double>&, std::pair<double, double>&, double);
  virtual ~AScale();

  virtual void	setSpeed(Ogre::Real);
  virtual Ogre::Real	getSpeed() const;
  virtual void	*getObject();
};

#endif
