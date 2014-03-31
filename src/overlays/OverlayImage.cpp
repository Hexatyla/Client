//
// MouseCursor.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
//
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
//
// Started on  Tue Jan 28 14:58:07 2014 Yannick Briffa
// Last update Tue Mar 11 16:53:58 2014 Yannick Briffa
//

#include	<iostream>
#include	"overlays/OverlayImage.hh"
#include	"utils/graphicException.hh"

OverlayImage::OverlayImage(std::string const &scene, std::string const &name, std::string const &file, ushort priority, bool locked)
  : AOverlay(scene, name, priority, locked), _file(file), _texture(NULL), _border(2), _rotated(false)
{
}

OverlayImage::~OverlayImage()
{
}

void		OverlayImage::init(AOverlay *parent)
{
  Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

  _material = Ogre::MaterialManager::getSingleton().create("M" + _scene + "/" + _file, "General");

  _container = static_cast<Ogre::BorderPanelOverlayElement *>(overlayManager.createOverlayElement("Panel", "C" + _scene + "/" + _name));
  _container->setMaterialName(_material->getName());

  if (!parent)
    createOverlay(_container);
  else {
    parent->getContainer()->addChild(_container);
    _parent = parent;
  }
  this->setImage(_file, _material, _texture);
}

void		OverlayImage::init(Ogre::Overlay *parent)
{
  Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

  _material = Ogre::MaterialManager::getSingleton().create("M" + _scene + "/" + _file, "General");

  _container = static_cast<Ogre::BorderPanelOverlayElement *>(overlayManager.createOverlayElement("Panel", "C" + _scene + "/" + _name));
  _container->setMaterialName(_material->getName());

  parent->add2D(_container);
  this->setImage(_file, _material, _texture);
}

void		OverlayImage::setImage(std::string const &filename, Ogre::MaterialPtr &material, Ogre::TextureUnitState *&texture)
{
  Ogre::TexturePtr		textureptr = Ogre::TextureManager::getSingleton().load(filename, "General");

  if(material->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
    texture = material->getTechnique(0)->getPass(0)->getTextureUnitState(0);
  else
    texture = material->getTechnique(0)->getPass(0)->createTextureUnitState( textureptr->getName() );
  texture->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
  material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
}

bool			OverlayImage::hoverHexagone(unsigned int x_max_i, unsigned int y_max_i, unsigned int border_i, bool rotate, unsigned int mouse_x_i, unsigned int mouse_y_i)
{
  double a, b;
  double x1, y1, x2, y2;

  double x_max    = static_cast<double>(x_max_i);
  double y_max    = static_cast<double>(y_max_i);
  double border   = static_cast<double>(border_i);
  double mouse_x  = static_cast<double>(mouse_x_i); 
  double mouse_y  = static_cast<double>(mouse_y_i);

  if (mouse_y > (y_max / 2))
    mouse_y = (y_max - 1) - mouse_y;
  if (mouse_x < (x_max / 2))
    mouse_x = ((x_max)/ 2) + (((x_max - 1)/ 2) - mouse_x);
  if (mouse_x >= (x_max - border) || mouse_y < border)
    return (false);
  mouse_y = -mouse_y;
  if (!rotate)
  {
    x1 = ((x_max - 1) / 2);
    y1 = -1 * (border);
    x2 = (y_max - border);
    y2 = -1 * ((x_max - (2 * border) + 2) / 4);
  }
  else
  {
    x1 = (y_max - border);
    y1 = -1 * ((x_max - 1) / 2);
    x2 = y_max - ((x_max - (2 * border) + 2) / 4);
    y2 = -1 * border;
  }
  a = (y1 - y2) / (x1 - x2);
  b = ((x1 * y2) - (x2 * y1)) / (x1 - x2);
  /*
  std::cout << "A(" << x1 << ";" << y1 << ")  B(" << x2 << ":" << y2 << ")" << std::endl;
  std::cout << "a = " << a << "; b = " << b << std::endl;
  std::cout << "y = ax + b = " << static_cast<int>(a * mouse_x + b) << " // my = " << mouse_y << " ; mx = " << mo    use_x<< std::endl;
  */
  if (static_cast<int>(a * mouse_x + b) < mouse_y)
  {
    return (false);
  }
  return (true);
}

bool			OverlayImage::isInside(unsigned int x, unsigned int y)
{
  return (hoverHexagone(_size.x, _size.y, _border, _rotated, x - _currentPos.x * _winSize.x, y - _currentPos.y * _winSize.y));
}

void			OverlayImage::setOpacity(Ogre::Real transparency)
{
  _texture->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, transparency);
}

void			OverlayImage::scaleTextX(Ogre::Real x)
{
  _texture->setTextureUScale(x);
}

void			OverlayImage::scaleTextY(Ogre::Real y)
{
  _texture->setTextureVScale(y);
}

void			OverlayImage::setRotated(bool fuckitclovis)
{
  _rotated = fuckitclovis;
}

bool			OverlayImage::isRotated() const
{
  return _rotated;
}

const std::string &OverlayImage::getFile() const
{
  return (_file);
}
