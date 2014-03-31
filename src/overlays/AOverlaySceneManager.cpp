//
// AOverlaySceneManager.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:07 2014 Yannick Briffa
// Last update Tue Mar 11 15:56:38 2014 Yannick Briffa
//

#include	<iterator>
#include	<algorithm>

#include	"applications/Application.hh"
#include	"overlays/AOverlaySceneManager.hh"
#include	"utils/graphicException.hh"

AOverlaySceneManager::AOverlaySceneManager(std::string const &name, ushort prio)
  : _name(name), _priority(prio), _isVisible(true)
{
}

AOverlaySceneManager::~AOverlaySceneManager()
{
}

AOverlay		*AOverlaySceneManager::getOverlay(std::string const &name)
{
  if (_overlayMap.size() < 1)
    throw graphicException("No Overlay Available in " + _name + " OverlaySceneManager");
  return _overlayMap[name];
}


void			  AOverlaySceneManager::insertOverlay(std::string const &name, AOverlay *overlay)
{
  if (overlay)
    _overlayMap[name] = overlay;
}

OverlayImage	*AOverlaySceneManager::addOverlayImage(Ogre::Vector2 const &winSize, Ogre::Vector2 const &size,
					 Ogre::Vector2 const &pos, std::string const &name,
           std::string const& pathname, bool locked, bool visible)
{
  OverlayImage *tmp = new OverlayImage(_name, name, pathname, _priority, locked);

  tmp->init();
  tmp->setVisible(visible);
  tmp->setSize(size);
  tmp->setWindowDimensions(winSize);
  tmp->updatePosition(pos);
  this->insertOverlay(name, tmp);
  return tmp;
}

OverlayText	*AOverlaySceneManager::addOverlayText(Ogre::Vector2 const &winSize, Ogre::Vector2 const &size,
					     Ogre::Vector2 const &pos, std::string const &name, std::string const &pathname,
					     std::string const &text, bool locked, bool visible)
{
  OverlayText *tmp = new OverlayText(_name, name, pathname, _priority, locked);

  tmp->init();
  tmp->setVisible(visible);
  tmp->setSize(size);
  tmp->setWindowDimensions(winSize);
  tmp->updatePosition(pos);
  tmp->setText(text);
  this->insertOverlay(name, tmp);
  return tmp;
}

InputText	*AOverlaySceneManager::addInputText(Ogre::Vector2 const &winSize, Ogre::Vector2 const &size,
					     Ogre::Vector2 const &pos, std::string const &name, std::string const &pathname,
					     std::string const &text, bool locked, bool visible)
{
  InputText *tmp = new InputText(_name, name, pathname, _priority, locked, false);

  tmp->init();
  tmp->setVisible(visible);
  tmp->setSize(size);
  tmp->setWindowDimensions(winSize);
  tmp->updatePosition(pos);
  tmp->setText(text);

  //EXEMPLE ICI CLOVIS TU NE ME PETERAS PAS LES COUILLES
  tmp->setTextPos(Ogre::Vector2(30,15));
  tmp->refreshPosition();
  // OUBLIE PAS LE REFRESH COMME CA TU WINNERAS PAS


  this->insertOverlay(name, tmp);
  return tmp;
}

Button	*AOverlaySceneManager::addButton(Ogre::Vector2 const &winSize, Ogre::Vector2 const &size, Ogre::Vector2 const &pos, std::string const &name, std::string const& pathname, bool locked, bool visible)
{
  Button *tmp = new Button(_name, name, pathname, _priority, locked);

  tmp->init();
  tmp->setVisible(visible);
  tmp->setSize(size);
  tmp->setWindowDimensions(winSize);
  tmp->updatePosition(pos);
  this->insertOverlay(name, tmp);
  return tmp;
}

void			AOverlaySceneManager::updateWindowDimension(unsigned int width, unsigned int height)
{
  for (auto it : _overlayMap)
    if ((it).second)
      (it).second->setWindowDimensions(Ogre::Vector2(width, height));
}


std::vector<AOverlay *>		AOverlaySceneManager::getOverlayAt(unsigned int x, unsigned int y)
{
  std::vector<AOverlay *>	res;

  for (auto it : _overlayMap)
    if ((it.second)->getName() != "black")
      {
	Ogre::Vector2 tmp = Application::getInstance()->convertToWindow(x, y);
	if ((it.second)->isVisible())
	  if (it.second->getContainer()->findElementAt(tmp.x, tmp.y) ||
	      (it.second->getParent() && it.second->getParent()->getContainer()->findElementAt(tmp.x, tmp.y)))
	    if ((it.second)->isInside(x, y))
	      res.push_back((it).second);
      }
  return res;
}

void		AOverlaySceneManager::applyOnAllMaterials(void (*ptr)(std::pair<const std::string, AOverlay *> &))
{
  for_each(_overlayMap.begin(), _overlayMap.end(), ptr);
}

void		AOverlaySceneManager::applyOnAllMaterialsExcept(void (*ptr)(std::pair<const std::string, AOverlay *> &), std::string const &except)
{
  for (auto it : _overlayMap)
    if ((it).first != except)
      ptr((it));
}

void		AOverlaySceneManager::setVisible(bool visi)
{
  _isVisible = visi;
  if (visi == false) {
    for (auto it : _overlayMap)
      if (it.second->isVisible() == true) {
	it.second->setVisible(false);
	_hideBefore.push_back(it.second);
      }
  }
  else {
    for (auto it : _hideBefore)
      it->setVisible(true);
    _hideBefore.clear();
  }
}

bool    AOverlaySceneManager::isVisible()
{
  return (_isVisible);
}

std::string const	&AOverlaySceneManager::getName() const
{
  return _name;
}


void			AOverlaySceneManager::delOverlay(std::string const &key)
{
  if (AOverlay *tmp = _overlayMap[key]) {
    for (std::deque<AOverlay *>::iterator it = _hideBefore.begin(); it != _hideBefore.end();)
      {
	if (*it = tmp)
	  it = _hideBefore.erase(it);
	else
	  ++it;
      }
    delete tmp;
    _overlayMap.erase(key);
  }
}
