//
// AOverlaySceneManager.hh for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:28 2014 Yannick Briffa
// Last update Mon Mar  3 12:16:12 2014 Yannick Briffa
//

#ifndef __AOVERLAYSCENEMANAGER_HH__
# define __AOVERLAYSCENEMANAGER_HH__

# include	<map>
# include	"overlays/AOverlay.hh"
# include	"overlays/Button.hh"
# include	"overlays/OverlayText.hh"
# include	"overlays/InputText.hh"

class AOverlaySceneManager
{
protected:
  std::string				_name;
  ushort				_priority;
  std::map<std::string, AOverlay *>	_overlayMap;
  std::deque<AOverlay *>		_hideBefore;

private:
  AOverlaySceneManager();
  bool  _isVisible;

public:
  AOverlaySceneManager(std::string const &, ushort);
  virtual ~AOverlaySceneManager();

  virtual void		init(unsigned int, unsigned int) = 0;

  AOverlay		*getOverlay(std::string const &);
  std::string const	&getName() const;

  virtual OverlayImage	*addOverlayImage(Ogre::Vector2 const &, Ogre::Vector2 const &,
                            Ogre::Vector2 const &, std::string const &, std::string const&,
                            bool = false, bool = true);
  virtual OverlayText	*addOverlayText(Ogre::Vector2 const &, Ogre::Vector2 const &,
                        Ogre::Vector2 const &, std::string const &, std::string const&, 
                        std::string const &,bool = false, bool = true);
  virtual InputText		*addInputText(Ogre::Vector2 const &, Ogre::Vector2 const &, Ogre::Vector2 const &,
                          std::string const &, std::string const &, std::string const&, bool = false, bool = false);
  Button			*addButton(Ogre::Vector2 const &, Ogre::Vector2 const &, Ogre::Vector2 const &,
                        std::string const &, std::string const&,
                        bool = false, bool = true);
  void			insertOverlay(std::string const &, AOverlay *);
  void			updateWindowDimension(unsigned int, unsigned int);


  void			applyOnAllMaterials(void (*)(std::pair<const std::string, AOverlay *> &));
  void			applyOnAllMaterialsExcept(void (*)(std::pair<const std::string, AOverlay *> &), std::string const &);


  std::vector<AOverlay *>	getOverlayAt(unsigned int, unsigned int);

  void			setVisible(bool);
  bool      isVisible();

  void			delOverlay(std::string const &);
};

#endif
