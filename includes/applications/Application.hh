//
// Application.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Fri Jan 24 15:39:24 2014 Yannick Briffa
// Last update Fri Mar  7 17:02:32 2014 gautier lefebvre
//

#ifndef	__APPLICATION_HH__
# define __APPLICATION_HH__

# include	<map>
# include	<iostream>
# include	"Ogre.h"
# include	"Overlay/OgreOverlaySystem.h"
# include	"overlays/AOverlaySceneManager.hh"
# include	"utils/graphicException.hh"
# include	"scene/AScene.hh"
# include "GUI/Controller.hpp"
# include "GUIG/Controller.hpp"
# include	"scene/MenuScene.hh"
# include	"Threading/Thread.hpp"
#include	"Singleton.hpp"

class	Application : public Singleton<Application>, public Ogre::WindowEventListener, public Ogre::FrameListener
{
  friend class	Singleton<Application>;

protected:
  bool					_exit;
  Ogre::Root				*_root;
  Ogre::String				_plugins;
  Ogre::String				_ressources;
  Ogre::RenderWindow			*_window;
  Ogre::FontManager			*_fontmanager;
  OIS::InputManager			*_inputmanager;
  OIS::Mouse				*_mouse;
  OIS::Keyboard				*_keyboard;
  Ogre::OverlaySystem			*_overlaySystem;
  AScene				*_currentScene;
  AOverlaySceneManager			*_cursorOverlay;
  OverlayImage				*_mousecursor;
  std::map<std::string, AScene *>	_sceneMap;
  Thread				*_thNetwork;

private:
  void		loadResources();
  void		createFrameListener();
  void		initInput();
  void		initScene();
  void		initOverlaySceneManager();
  bool		init(const std::string &, int);

protected:
  virtual void	windowResized(Ogre::RenderWindow* rw);
  virtual void	windowClosed(Ogre::RenderWindow* rw);
  virtual bool	frameRenderingQueued(const Ogre::FrameEvent& evt);

public:
  Application();
  ~Application();

  bool		exec(const std::string &, int);
  void		close();
  void		setViewport(std::string const &);
  void		exit();
  void		reconnect();

  Ogre::OverlaySystem	*getOverlaySystem();
  OverlayImage		*getMouseCursor();

  AOverlaySceneManager *getAOverlayCursor();

  Ogre::Vector2		convertToWindow(unsigned int, unsigned int);
};

#endif //   __APPLICATION_HH__ !
