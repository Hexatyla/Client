//
// AOverlaySceneManager.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:28 2014 Yannick Briffa
// Last update Mon Feb  3 22:38:17 2014 Yannick Briffa
//

#ifndef __MOUSEOVERLAYMANAGER_HH__
# define __MOUSEOVERLAYMANAGER_HH__

# include	"overlays/AOverlaySceneManager.hh"

class MouseOverlayManager : public AOverlaySceneManager
{
public:
  MouseOverlayManager();
  virtual ~MouseOverlayManager();

  virtual void		init(unsigned int, unsigned int);
};

#endif
