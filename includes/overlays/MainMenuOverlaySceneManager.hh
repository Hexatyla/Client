//
// AOverlaySceneManager.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:28 2014 Yannick Briffa
// Last update Tue Feb 18 14:17:09 2014 Yannick Briffa
//

#ifndef __MAINMENUOVERLAYSCENEMANAGER_HH__
# define __MAINMENUOVERLAYSCENEMANAGER_HH__

# include	"overlays/AOverlaySceneManager.hh"

class MainMenuOverlaySceneManager : public AOverlaySceneManager
{
public:
  MainMenuOverlaySceneManager();
  virtual ~MainMenuOverlaySceneManager();

  virtual void		init(unsigned int, unsigned int);
};

#endif
