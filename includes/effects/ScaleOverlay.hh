//
// Scaleoverlayin.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:02:29 2014 Yannick Briffa
// Last update Tue Feb 11 13:34:39 2014 Yannick Briffa
//

#ifndef	__SCALEOVERLAY_HH__
# define __SCALEOVERLAY_HH__

# include	"effects/AFade.hh"

class	ScaleOverlay : public AFade
{
public:
  ScaleOverlay(Overlay *, double, double, double);
  virtual ~ScaleOverlay();

  virtual bool	update(const Ogre::FrameEvent &);
};

#endif
