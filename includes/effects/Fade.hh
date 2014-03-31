//
// Fadein.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:02:29 2014 Yannick Briffa
// Last update Wed Feb 12 15:36:09 2014 Yannick Briffa
//

#ifndef	__FADE_HH__
# define __FADE_HH__

# include	"effects/AFade.hh"

class	Fade : public AFade
{
public:
  Fade(OverlayImage *, double, double, double);
  virtual ~Fade();

  virtual bool	update(const Ogre::FrameEvent &);
};

#endif
