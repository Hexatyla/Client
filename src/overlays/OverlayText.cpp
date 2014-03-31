//
// MouseCursor.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
//
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
//
// Started on  Tue Jan 28 14:58:07 2014 Yannick Briffa
// Last update Fri Mar 21 16:17:18 2014 gautier lefebvre
//

#include	<iostream>
#include	"overlays/OverlayText.hh"
#include	"utils/graphicException.hh"
#include	"utils/convert.hpp"
#include	"OgreTextAreaOverlayElement.h"
#include	"applications/Application.hh"

OverlayText::OverlayText(std::string const &scene, std::string const &name, std::string const &file, ushort priority, bool locked)
  : AOverlay(scene, name, priority, locked), _text(""), _backgroundFile(file), _background(NULL), _color(Ogre::ColourValue(1,1,1)), _paddingWith(0), _paddingHeight(0)
{
}

OverlayText::~OverlayText()
{
  if (_background)
    delete _background;
}

void		OverlayText::init(AOverlay *parent)
{
  _background = new OverlayImage(_scene, "background" + _name, _backgroundFile, _priority, _locked);
  _background->init(parent);

  _parent = _background;
  Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

  _container = static_cast<Ogre::OverlayContainer *>(overlayManager.createOverlayElement("TextArea", "T" + _scene + "/" + _name));
  _container->setColour(_color);

  setFont("BerlinSans32");

  setSizeFont(72);
  _background->getOverlay()->add2D(_container);
  _guiOverlay = _background->getOverlay();
  setTextPos(Ogre::Vector2(0,0));
}

void		OverlayText::init(Ogre::Overlay *parent)
{
  _background = new OverlayImage(_scene, "background" + _name, _backgroundFile, _priority, _locked);
  _background->init(parent);

  _parent = _background;
  Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

  _container = static_cast<Ogre::OverlayContainer *>(overlayManager.createOverlayElement("TextArea", "T" + _scene + "/" + _name));
  _container->setColour(_color);

  setFont("BerlinSans32");

  setSizeFont(72);
  _background->getOverlay()->add2D(_container);
  setTextPos(Ogre::Vector2(0,0));
}

//
//		VIRTUAL
//

void		OverlayText::setVisible(bool visi)
{
  _background->setVisible(visi);
  if (visi)
    _container->show();
  else
    _container->hide();
}

void		OverlayText::setPos(Ogre::Vector2 const &toCopy)
{
  _background->setPos(toCopy);
}

void	OverlayText::setSize(Ogre::Vector2 const &size)
{
  _background->setSize(size);
  AOverlay::setSize(size);
}

void	OverlayText::setWindowDimensions(Ogre::Vector2 const &size)
{
  _background->setWindowDimensions(size);
  AOverlay::setWindowDimensions(size);
}

void	OverlayText::updatePosition(Ogre::Vector2 const &pos)
{
 _background->updatePosition(pos);
  refreshPosition();
}

void	OverlayText::refreshPosition()
{
  Ogre::Vector2		tmp;
  _background->refreshPosition();
  const Ogre::Vector2 &bg = _background->getPos();

  tmp.x = (bg.x + (_paddingHeight / _winSize.x));
  tmp.y = (bg.y + (_paddingWith / _winSize.y));

  _container->setPosition(clamp(tmp.x, 0.0f, 1.0f), clamp(tmp.y, 0.0f, 1.0f));
}

//
//
//

void		OverlayText::setText(std::string const &text)
{
  _text = text;
  _container->setCaption(text);
}

void		OverlayText::updateText()
{
  _container->setCaption(_text);
}

std::string const	&OverlayText::getText() const
{
  return _text;
}


Ogre::Vector2 const	&OverlayText::getTextSize()
{
  return _size;
}

void		OverlayText::setTextPos(Ogre::Vector2 const &pos)
{
  AOverlay::setPos(pos);
}

Ogre::Vector2 const	&OverlayText::getTextPos() const
{
  return _currentPos;
}

void		OverlayText::setColor(Ogre::ColourValue const &color)
{
  _color = color;
  _container->setColour(_color);
}

void		OverlayText::setFont(std::string const &name)
{
  _container->setParameter("font_name", name);
}

void		OverlayText::setSizeFont(unsigned int size)
{
  _container->setMetricsMode(Ogre::GMM_PIXELS);
  _container->setParameter("char_height", toString(static_cast<double>(size) / _winSize.y));
  _container->setMetricsMode(Ogre::GMM_RELATIVE);
}

bool			OverlayText::isInside(unsigned int x, unsigned int y)
{
  return (true);
}

void			OverlayText::center()
{
  std::cout << "Parent size "<< _parent->getSize() << std::endl;
  std::cout << "MYSIZE " << getSize() << std::endl;
}

void      OverlayText::setPaddingWidth(int v)
{
  _paddingWith = v;
  this->refreshPosition();
}

void    OverlayText::setPaddingHeight(int v)
{
  _paddingHeight = v;
  this->refreshPosition();
}

void	OverlayText::setOpacity(Ogre::Real val) {
  this->_background->setOpacity(val);
}
