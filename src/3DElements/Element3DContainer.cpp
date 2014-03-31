//
// Element3DContainer.cpp for pfa in /home/yannick/Documents/pfa
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Mar  4 11:50:17 2014 Yannick Briffa
// Last update Wed Mar 26 16:29:47 2014 geoffrey bauduin
//

#include	"3DElements/Element3DContainer.hh"

Element3DContainer::Element3DContainer()
: _icon(NULL), _light(NULL), _model(NULL), _node(NULL), _sceneManager(NULL), _modelType("Ukwn"), _name(""), _visibility(true), _orientation(0)
{
  // for (unsigned int i = 0; i < NBSOUNDELEMENT; ++i)
  //   _soundList[i] = NULL;
}

Element3DContainer::~Element3DContainer()
{
}

void	Element3DContainer::init(Ogre::SceneManager *scnMgr, std::string const &name, std::string const &model, OverlayImage *icon, const std::string &modelType)
{
  _sceneManager =scnMgr;
  _icon = icon;
  _modelType = modelType;
  _name = name;

  _model = _sceneManager->createEntity("M_" + name, model);
  _node = _sceneManager->getRootSceneNode()->createChildSceneNode("N_" + name);
  _node->attachObject(_model);
  _orientation = 0;
}

void	Element3DContainer::setSound(Element3DContainer::Sound sound, std::string const &value)
{
  if (Sound::CREATION <= sound && sound <= Sound::ATTACK)
    _soundList[sound] = value;
}

void	Element3DContainer::playSound(Element3DContainer::Sound sound)
{

}

std::string const	&Element3DContainer::getType() const
{
  return _modelType;
}

bool			Element3DContainer::operator==(std::string const &value)
{
  return (_modelType == value);
}

AOverlay		*Element3DContainer::getIcon()
{
  return _icon;
}


void			Element3DContainer::setPos(Ogre::Vector3 const &pos)
{
  _node->translate(pos);
}

void			Element3DContainer::setPos(double x, double y, double z)
{
  _node->translate(Ogre::Vector3(x, y, z));
}

Ogre::SceneNode		*Element3DContainer::getNode()
{
  return _node;
}

bool  Element3DContainer::getVisible()
{
  return (_visibility);
}

void  Element3DContainer::setVisible(bool v)
{
  Ogre::SceneNode *e = getNode();
  _visibility = v;
  e->setVisible(v);
}

void  Element3DContainer::setInvisible()
{
  this->setVisible(false);
}

void		Element3DContainer::delAffiNodeParent()
{
  if (_node->getParent())
    _node->getParent()->removeChild(_node);
}

void  Element3DContainer::setPosition(const Ogre::Vector3 &pos)
{
  Ogre::SceneNode *e = getNode();
  e->setPosition(pos);
}

void  Element3DContainer::setPosition(double x, double y, double z)
{
  Ogre::SceneNode *e = getNode();
  setPosition(Ogre::Vector3(x, y, z));
}

void			Element3DContainer::setPositionCenter(Ogre::Vector3 const &pos)
{
  Ogre::AxisAlignedBox bbox = this->_model->getBoundingBox();
  Ogre::Vector3 size = bbox.getSize();
  _node->setPosition(Ogre::Vector3(pos.x - size.x / 2.0, pos.y + size.y / 2.0, pos.z));
}

void			Element3DContainer::setPositionCenter(double x, double y, double z)
{
  this->setPositionCenter(Ogre::Vector3(x, y, z));
}

const std::string &Element3DContainer::getName() const
{
  return (_name);
}

void  Element3DContainer::setOrientation(int o)
{
  Ogre::Vector3 v(0.0, 1.0, 0.0);
  Ogre::Degree r(_orientation - o);
  this->getNode()->rotate(v, r);
  _orientation = o;
}

void  Element3DContainer::toLittle()
{
  Ogre::SceneNode *e = getNode();
  e->setScale(0.2f, 0.2f, 0.2f);
}

const std::string &Element3DContainer::getIconName() const
{
  return (_icon->getFile());
}

Ogre::Light  *Element3DContainer::getLight(void)
{
  return (_light);
}

void  Element3DContainer::setLight(Ogre::Light *light)
{
  _light = light;
}





