//
// AOverlay.hh for pfa in /home/yannick/Documents/pfa/graphicClient/includes/overlays
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Wed Feb 12 14:32:01 2014 Yannick Briffa
// Last update Sat Mar 15 11:11:25 2014 Yannick Briffa
//

#ifndef __AOVERLAY_HH__
# define __AOVERLAY_HH__

# include	"Ogre.h"
# include	"Overlay/OgreOverlayContainer.h"
# include	"Overlay/OgreOverlayManager.h"
# include	"OgreBorderPanelOverlayElement.h"

class AOverlay
{
protected:
  std::string			_scene;
  std::string			_name;
  ushort			_priority;
  bool				_locked;
  bool				_isAlreadyDeleted;
  Ogre::Overlay			*_guiOverlay;
  Ogre::OverlayContainer	*_container;
  AOverlay			*_parent;
  Ogre::Vector2			_currentPos;
  Ogre::Vector2			_size;
  Ogre::Vector2			_winSize;

public:
  AOverlay(std::string const &, std::string const &, ushort, bool = false);
  virtual ~AOverlay();

public:
  //		PURE

  virtual void	init(AOverlay * = NULL) = 0;
  virtual void	init(Ogre::Overlay *) = 0;
  virtual bool	isInside(unsigned int, unsigned int) = 0;

public:
  //		GETTER SETTER

  Ogre::OverlayContainer	*getContainer();
  Ogre::Overlay			*getOverlay();
  AOverlay			*getParent();

  Ogre::Vector2 const	&getPos() const;
  Ogre::Vector2		getPosInWindow() const;
  virtual void		setPos(Ogre::Vector2 const &toCopy);

  virtual void	setVisible(bool visible);
  bool		isVisible() const;

  virtual void	setSize(Ogre::Vector2 const &);
  Ogre::Vector2 const &getSize();
  void		updateSize();

  virtual void	setWindowDimensions(Ogre::Vector2 const &);

  bool		isLocked() const;
  void		setLocked(bool);

  void		reinitZOrder();
  void		changeZOrder(short);
  ushort	getZOrder();

  std::string const	&getName() const;
  std::string const	&getScene() const;

public:
  //		UTILS

  Ogre::Real	clamp(Ogre::Real a, Ogre::Real min, Ogre::Real max);
  virtual void		updatePosition(Ogre::Vector2 const &);
  virtual void		updatePosition(int, int);
  virtual void		refreshPosition();
  void		createOverlay(Ogre::OverlayContainer *contain);

  void		setRelative();
  void		setPx();

public:
  void		setDeleting(bool);
};

#endif
