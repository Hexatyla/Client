//
// Fadein.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 10:02:29 2014 Yannick Briffa
// Last update Wed Feb 12 16:00:54 2014 Yannick Briffa
//

#ifndef	__SCALE_HH__
# define __SCALE_HH__

# include	"effects/AScale.hh"

class	Scale : public AScale
{
public:
  Scale(OverlayImage *, std::pair<double, double> &, std::pair<double, double> &, double);
  virtual ~Scale();

  virtual bool	update(const Ogre::FrameEvent &);
};

#endif
