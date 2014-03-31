//
// AScene.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sat Jan 25 13:48:14 2014 Yannick Briffa
// Last update Fri Mar  7 17:45:31 2014 Yannick Briffa
//

#ifndef __ASCENE_HH__
# define __ASCENE_HH__

# include	"Ogre.h"
# include	"OIS.h"
# include	"utils/graphicException.hh"
# include	"effects/IEffect.hh"
# include	"overlays/AOverlaySceneManager.hh"
# include	"overlays/OverlayImage.hh"
# include	"overlays/InputText.hh"

class	AScene : public OIS::MouseListener, public OIS::KeyListener
{
private:
  AScene();

protected:
  std::string		_name;
  Ogre::RenderWindow	*_window;
  Ogre::SceneManager	*_sceneMgr;
  Ogre::Camera		*_camera;
  Ogre::Viewport	*_viewport;
  Ogre::ColourValue	_background;

  InputText		*_currentInput;
  AOverlay		*_currentOn;
  AOverlay		*_currentClick;

  Ogre::RaySceneQuery	*_raySceneQuery;
  bool			_leftClickDown;
  bool			_rightClickDown;
  Ogre::Entity		*_objectClick;

  std::list<IEffect *>	_listMove;
  std::map<std::string, AOverlaySceneManager *>			_overlayManagerMap;
  std::map<std::string, bool>			                  _overlayManagerMapv;
  std::map<AOverlay *, bool (*)(AScene *, AOverlay *)>		_subscribed;

public:
  AScene(std::string const &, Ogre::RenderWindow *, Ogre::ColourValue const & = Ogre::ColourValue(0,0,0));
  AScene(AScene const &);
  virtual ~AScene();

  void				init(Ogre::Root *);
  std::string const		&getName() const;
  AOverlaySceneManager		*getOverlaySceneManager(std::string const &);
  Ogre::ColourValue const	&getBackgroundColor() const;
  void				addEffect(IEffect *);

  virtual void		createScene() = 0;
  virtual bool		updateFrame(const Ogre::FrameEvent &);
  virtual void		createCamera();
  virtual void		createViewport();
  virtual bool		mouseMoved(const OIS::MouseEvent &e);

  void	delViewport();

  void	pickFirstObject3DOnClick(const OIS::MouseEvent &e);
  void	clearListMove();

  void	subscribe(AOverlay *, bool (*)(AScene *, AOverlay *));
  bool	executeSubscribe(AOverlay *);

  void	deleteOverlayWithEffect(AOverlay *);

  void  setVisible(bool);
};

#endif
