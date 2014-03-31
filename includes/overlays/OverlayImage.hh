//
// Overlay.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/applications
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 14:46:25 2014 Yannick Briffa
// Last update Tue Mar 11 16:54:37 2014 Yannick Briffa
//

#ifndef __OVERLAYIMAGE_HH__
# define __OVERLAYIMAGE_HH__

# include	"overlays/AOverlay.hh"

class OverlayImage : public AOverlay
{
protected:
  std::string			_file;
  Ogre::TextureUnitState	*_texture;
  Ogre::MaterialPtr		_material;
  unsigned int			_border;
  bool				_rotated;

private:
  OverlayImage();

public:
  OverlayImage(std::string const &, std::string const &, std::string const &, ushort,
      bool = false);
  virtual ~OverlayImage();

public:
  virtual void	init(AOverlay * = NULL);
  virtual void	init(Ogre::Overlay *);
  bool	hoverHexagone(unsigned int x_max, unsigned int y_max, unsigned int border, bool rotate, unsigned int mouse_x, unsigned int mouse_y);
  virtual bool	isInside(unsigned int, unsigned int);

public:
  void		setImage(std::string const &, Ogre::MaterialPtr &, Ogre::TextureUnitState *&);

  Ogre::MaterialPtr		&getMaterial();
  Ogre::TextureUnitState	*getTexture();

  const std::string &getFile() const;

  void		setOpacity(Ogre::Real);
  void		scaleTextX(Ogre::Real);
  void		scaleTextY(Ogre::Real);

  void		setRotated(bool);
  bool		isRotated() const;
};

#endif
