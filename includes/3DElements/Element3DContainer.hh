//
// 3DElementContainer.hh for PFA in /home/yannick/Documents/pfa/includes/3DElements
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Mar  4 10:12:56 2014 Yannick Briffa
// Last update Wed Mar 26 16:22:18 2014 geoffrey bauduin
//

#ifndef	__ELEMENT3DCONTAINER_HH__
# define __ELEMENT3DCONTAINER_HH__

# include	"Ogre.h"
# include	"overlays/OverlayImage.hh"


# define NBSOUNDELEMENT 4

class	Element3DContainer
{
public:
  typedef enum
    {
      CREATION = 0,
      DEATH,
      BASE,
      ATTACK
    } Sound;

private:
  OverlayImage		*_icon;
  std::string		_soundList[4];
  Ogre::Light     *_light;
  Ogre::Entity		*_model;
  Ogre::SceneNode	*_node;
  Ogre::SceneManager	*_sceneManager;
  std::string		_modelType;
  std::string   _name; // franchement....
  bool          _visibility; // ....
  int	_orientation;

public:
  Element3DContainer();
  ~Element3DContainer();

  void		init(Ogre::SceneManager *scnMgr, std::string const &name, std::string const &model, OverlayImage *icon, const std::string &modelType);
  void		setSound(Sound Key, std::string const &value);
  void		playSound(Sound Key);
  std::string const	&getType() const;

  bool		operator==(std::string const &);

  AOverlay	*getIcon();

  void		setPos(Ogre::Vector3 const &);
  void		setPos(double x, double y, double z);
  void		setPositionCenter(const Ogre::Vector3 &);
  void		setPositionCenter(double, double, double);
  void    setVisible(bool = true);
  void    setInvisible();
  bool    getVisible();
  const std::string &getName() const;
  const std::string &getIconName() const;
  
  void    setPosition(const Ogre::Vector3&);
  void    setPosition(double, double, double);
  void    setOrientation(int);

  void    setLight(Ogre::Light *);
  Ogre::Light     *getLight();
  Ogre::SceneNode	*getNode();
  void		delAffiNodeParent();
  void    toLittle();
};

#endif
