//
// MouseCursor.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
//
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
//
// Started on  Tue Jan 28 14:58:07 2014 Yannick Briffa
// Last update Sat Mar 15 12:17:16 2014 Yannick Briffa
//

#include	<iostream>
#include	"overlays/AOverlay.hh"
#include	"utils/graphicException.hh"

AOverlay::AOverlay(std::string const &scene, std::string const &name, ushort priority, bool locked)
  : _scene(scene), _name(name), _priority(priority), _locked(locked), _isAlreadyDeleted(false), _guiOverlay(NULL),_container(NULL), _parent(NULL), _currentPos(Ogre::Real(0), Ogre::Real(0)), _size(Ogre::Real(0), Ogre::Real(0)), _winSize(Ogre::Real(0), Ogre::Real(0))
{
}

AOverlay::~AOverlay()
{
  if (!_isAlreadyDeleted)
    if (_container) {
      if (_guiOverlay)
	_guiOverlay->remove2D(_container);
      Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(_container);
    }
}


//
//			GETTER // SETTER
//


Ogre::OverlayContainer        *AOverlay::getContainer()
{
  return _container;
}

Ogre::Overlay		*AOverlay::getOverlay()
{
  return (_guiOverlay ? _guiOverlay : _parent->getOverlay());
}

AOverlay		*AOverlay::getParent()
{
  return _parent;
}


Ogre::Vector2 const	&AOverlay::getPos() const
{
  return _currentPos;
}

Ogre::Vector2	AOverlay::getPosInWindow() const
{
  return Ogre::Vector2(_currentPos.x * _winSize.x, _currentPos.y * _winSize.y);
}

void			AOverlay::setPos(Ogre::Vector2 const &toCopy)
{
  _currentPos = toCopy;
}





void		AOverlay::setVisible(bool visible)
{
  if (_container) {
    if (visible)
      _container->show();
    else
      _container->hide();
  }
  if (_parent != NULL)
    _parent->setVisible(visible);
}

bool		AOverlay::isVisible() const
{
  return _container->isVisible();
}



void	AOverlay::setSize(Ogre::Vector2 const &size)
{
  _size = size;
}

Ogre::Vector2 const	&AOverlay::getSize()
{
  return _size;
}

void	AOverlay::updateSize()
{
  _container->setWidth(_size.x / _winSize.x);
  _container->setHeight(_size.y / _winSize.y);
}


void	AOverlay::setWindowDimensions(Ogre::Vector2 const &size)
{
  _winSize.x = (size.x > 0) ? size.x : 1;
  _winSize.y = (size.y > 0) ? size.y : 1;

  updateSize();
}





bool		AOverlay::isLocked() const
{
  return _locked;
}

void		AOverlay::setLocked(bool lock)
{
  _locked = lock;
}






std::string const	&AOverlay::getName() const
{
  return _name;
}

std::string const	&AOverlay::getScene() const
{
  return _scene;
}





void			AOverlay::reinitZOrder()
{
  getOverlay()->setZOrder(_priority);
}

void			AOverlay::changeZOrder(short toadd)
{
  getOverlay()->setZOrder(_priority + toadd);
}

ushort			AOverlay::getZOrder()
{
  return getOverlay()->getZOrder();
}




//
//		UTILS
//

void			AOverlay::refreshPosition()
{
  _container->setPosition(clamp(_currentPos.x, 0.0f, 1.0f), clamp(_currentPos.y, 0.0f, 1.0f));
}


void		AOverlay::updatePosition(Ogre::Vector2 const &pos)
{
  _currentPos.x = pos.x / _winSize.x;
  _currentPos.y = pos.y / _winSize.y;
  refreshPosition();
}

void    AOverlay::updatePosition(int x, int y)
{
  updatePosition(Ogre::Vector2(x, y));
}

Ogre::Real	AOverlay::clamp(Ogre::Real a, Ogre::Real min, Ogre::Real max)
{
  return (a < min ? min : (a > max ? max : a));
}

void		AOverlay::createOverlay(Ogre::OverlayContainer *contain)
{
  std::string	name = "M" + _scene + "/" + _name;

  if (!(_guiOverlay = Ogre::OverlayManager::getSingletonPtr()->getByName(name)))
    _guiOverlay = Ogre::OverlayManager::getSingletonPtr()->create(name);
  _guiOverlay->setZOrder(_priority);
  _guiOverlay->add2D(contain);
  _guiOverlay->show();
}

void		AOverlay::setRelative()
{
  _container->setMetricsMode(Ogre::GuiMetricsMode::GMM_RELATIVE);
}

void		AOverlay::setPx()
{
  _container->setMetricsMode(Ogre::GuiMetricsMode::GMM_PIXELS);
}


void		AOverlay::setDeleting(bool th)
{
  _isAlreadyDeleted = th;
}
