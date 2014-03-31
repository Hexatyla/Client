//
// Element3DPoolManager.cpp for pfa in /home/yannick/Documents/pfa
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Mar  4 14:13:32 2014 Yannick Briffa
// Last update Mon Mar 31 12:50:33 2014 geoffrey bauduin
//

#include	"3DElements/Element3DPoolManager.hh"
#include	"3DElements/Element3DContainer.hh"
#include	"Utils/graphicException.hh"
#include	"Factory/Client.hpp"
#include	"Utils/convert.hpp"

#define	NBINSTANCEINIT	1

Element3DPoolManager::Element3DPoolManager()
  : _sceneMgr(NULL)
{
}

Element3DPoolManager::~Element3DPoolManager()
{

}

void			Element3DPoolManager::initOverlays(std::vector<Kernel::Serial> const & vector)
{
  for (auto it : vector)
    {
      const Kernel::Data	*ptr = Kernel::Manager::getInstance()->getData(it);

      if (!it.empty())
	_icons[it] = new OverlayImage("InGame", "icon_" + it, ptr->icon, 50, true);
    }
}

void			Element3DPoolManager::init(Ogre::SceneManager *sceneMgr, std::vector<Kernel::Serial> const & vector)
{
  _sceneMgr = sceneMgr;
  initOverlays(vector);

  for (auto it : vector)
    for (unsigned int i = 0; i < NBINSTANCEINIT; ++i)
      createElement(it);
}


Element3DContainer	*Element3DPoolManager::getElement(Kernel::Serial const &name)
{
  Element3DContainer	*tmp = NULL;

  // if (_pool.find(name) == _pool.end())
  //   throw graphicException("Unknow element type");

  if (!_pool[name].empty()) {
    tmp = _pool[name].front();
    _pool[name].pop();
  }
  else
    tmp = createElement(name);

  return tmp;
}

void			Element3DPoolManager::deleteElement(Element3DContainer *ptr)
{
  if (!ptr)
    throw graphicException("Can't delete NULL element fucking retard");
  _pool[ptr->getType()].push(ptr);
}

Element3DContainer	*Element3DPoolManager::createElement(Kernel::Serial const &name)
{
  const Kernel::Data	*ptr = Kernel::Manager::getInstance()->getData(name);

  if (!ptr)
    throw graphicException("Je throw parceque si ça faille c'est le serveur qui a planté");

  Element3DContainer	*element = Factory::Client::Element3D::create(_sceneMgr, "element3D_" + name + "_nb_" + toString(_countModel[name]), ptr->model, _icons[name], name);

  _countModel[name] += 1;

  if (!ptr->voice.empty())
    element->setSound(Element3DContainer::BASE, ptr->voice);
  if (!ptr->voiceBirth.empty())
    element->setSound(Element3DContainer::CREATION, ptr->voiceBirth);
  if (!ptr->voiceDie.empty())
    element->setSound(Element3DContainer::DEATH, ptr->voiceDie);
  if (!ptr->voiceAttack.empty())
    element->setSound(Element3DContainer::ATTACK, ptr->voiceAttack);
  element->setInvisible();
  element->toLittle();
  return element;
}
