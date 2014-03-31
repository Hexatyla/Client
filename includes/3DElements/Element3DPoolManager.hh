//
// Element3DPoolManager.hh for pfa in /home/yannick/Documents/pfa
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Mar  4 11:11:50 2014 Yannick Briffa
// Last update Thu Mar 13 17:41:28 2014 Yannick Briffa
//

#ifndef __ELEMENT3DPOOLMANAGER_HH__
# define __ELEMENT3DPOOLMANAGER_HH__

# include	<list>
# include	<map>
# include	"overlays/OverlayImage.hh"
# include	"Kernel/Serial.hpp"
# include	"Kernel/Data.hpp"
# include	"Kernel/Manager.hpp"

class Element3DContainer;

class	Element3DPoolManager
{
private:
  Ogre::SceneManager						*_sceneMgr;
  std::map<Kernel::Serial, std::queue<Element3DContainer *> >	_pool;
  std::map<Kernel::Serial, OverlayImage *>			_icons;
  std::map<Kernel::Serial, unsigned int>			_countModel;

public:
  Element3DPoolManager();
  ~Element3DPoolManager();

  void			initOverlays(std::vector<Kernel::Serial> const & vector);

  void			init(Ogre::SceneManager *scene, std::vector<Kernel::Serial> const & vector);

  Element3DContainer	*getElement(Kernel::Serial const &);
  void			deleteElement(Element3DContainer *);

  Element3DContainer	*createElement(Kernel::Serial const &);
};

#endif
