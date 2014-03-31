//
// MiniMap.cpp for  in /home/yannick/Documents/pfa
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Mar 11 16:20:39 2014 Yannick Briffa
// Last update Mon Mar 24 12:15:49 2014 Gautier Lefebvre
//

#include	"GUIG/MiniMap.hpp"

GUIG::Minimap::Minimap(ushort priority, Ogre::Vector2 const &size)
  : AGUIG(), AOverlaySceneManager("GameMinimap", 10), _size(size), _lookPos(size / 10), _currentScroll(MINSCROLL), _mainOverlay(NULL), _border(NULL), _minimap(NULL), _borderLook(NULL), _plus(NULL), _minus(NULL)
{
}

GUIG::Minimap::~Minimap()
{
  if (_minimap)
    delete _minimap;
  if (_borderLook)
    delete _borderLook;
  if (_plus)
    delete _plus;
  if (_minus)
    delete _minus;
  if (_mainOverlay)
    delete _mainOverlay;
}


void		GUIG::Minimap::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2	win(winX, winY);
  Ogre::Vector2 size;

  _minimap = addButton(win, _size, Ogre::Vector2(0,0), "minimap_moveLook_map", "testFile.png", true, true);
  _minimap->changeZOrder(0);
  _border = addButton(win, _size, Ogre::Vector2(0,0), "minimap_moveLook_border", "border_gayblue.png", true, true);

  size = _size / 5;

  _borderLook = addOverlayImage(win, size, _lookPos, "minimap_moveLook_borderlook", "border_red.png");
  _borderLook->changeZOrder(1);

  _borderLookSize[0] = size;
  for (unsigned int i = 1; i <= MAXSCROLL; ++i)
    _borderLookSize[i] = _borderLookSize[i - 1] * 1.2;

  size = Ogre::Vector2(33, 37);

  _plus = addButton(win, size, Ogre::Vector2(_size.x - size.x, this->_y + 20), "plusbutton", "profil_add.png");
  _plus->changeZOrder(3);
  _minus = addButton(win, size, Ogre::Vector2(_size.x - size.x, 110), "minusbutton", "profil_min.png");
  _minus->changeZOrder(3);
}


void		GUIG::Minimap::draw()
{
  Ogre::Vector2	pos(_x, _y);

  _minimap->updatePosition(pos);
  _border->updatePosition(pos);
  _borderLook->updatePosition(pos + _lookPos);

  pos += Ogre::Vector2(_size.x + this->_x - 70, 10);
  _plus->updatePosition(pos);
  pos.y += 48;
  _minus->updatePosition(pos);

}

bool GUIG::Minimap::canScrollDown()
{
  if (_currentScroll < MAXSCROLL)
    return true;
  return (false);
}

bool  GUIG::Minimap::canScrollUp()
{
  if (_currentScroll > MINSCROLL)
    return (true);
  return (false);
}

GUIG::Minimap		&GUIG::Minimap::operator++(int ignore)
{
  if (_currentScroll < MAXSCROLL) {
    Ogre::Vector2	size;
    Ogre::Vector2	center;

    _currentScroll++;

    center = _borderLook->getPosInWindow() + _borderLook->getSize() / 2;

    size = _borderLookSize[_currentScroll];
    _borderLook->setSize(size);
    _borderLook->updateSize();

    center -= (size / 2);
    _borderLook->updatePosition(center);
  }
  return (*this);
}

GUIG::Minimap		&GUIG::Minimap::operator--(int ignore)
{
  if (_currentScroll > MINSCROLL) {
    Ogre::Vector2	size;
    Ogre::Vector2	center;

    _currentScroll--;

    center = _borderLook->getPosInWindow() + _borderLook->getSize() / 2;

    size = _borderLookSize[_currentScroll];
    _borderLook->setSize(size);
    _borderLook->updateSize();

    center -= (size / 2);
    _borderLook->updatePosition(center);
  }
  return (*this);
}

Button		*GUIG::Minimap::getPlusButton()
{
  return _plus;
}

Button		*GUIG::Minimap::getMinusButton()
{
  return _minus;
}

const Ogre::Vector2 &GUIG::Minimap::getPosition()
{
  return (_minimap->getPos());
}

const Ogre::Vector2 &GUIG::Minimap::getSize() const
{
  return (_size);
}

const Ogre::Vector2 &GUIG::Minimap::getLookPosition() const {
  return (this->_lookPos);
}

void		GUIG::Minimap::moveLook(Ogre::Vector2 const &centerLooked)
{
  _lookPos = centerLooked;
  Ogre::Vector2	center = _borderLook->getPosInWindow() + _borderLook->getSize() / 2;
  Ogre::Vector2 newcenter = centerLooked * _size + Ogre::Vector2(_x, _y);

  _borderLook->updatePosition(_borderLook->getPosInWindow() + (newcenter - center));
}
