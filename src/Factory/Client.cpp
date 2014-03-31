//
// Client.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Thu Mar  6 13:27:16 2014 geoffrey bauduin
// Last update Thu Mar  6 13:52:51 2014 geoffrey bauduin
//

#include	"Factory/Pool.hpp"
#include	"Factory/Client.hpp"

static Pool< ::Element3DContainer> *pool3DElement = NULL;

void	Factory::Client::init(void) {
  Logger::getInstance()->log("Initializing client pools", Logger::INFORMATION);

  pool3DElement = new Pool< ::Element3DContainer>(500, 200, "Element3DContainer");

  Logger::getInstance()->log("Client pools have been initialized.", Logger::INFORMATION);
}

void	Factory::Client::end(void) {
  Logger::getInstance()->log("Deleting client pools", Logger::INFORMATION);
  delete pool3DElement;
}

::Element3DContainer	*Factory::Client::Element3D::create(Ogre::SceneManager *scnMgr, const std::string &name,
							    const std::string &model,
							    OverlayImage *icon, const std::string &modelType) {
  ::Element3DContainer *item = pool3DElement->get();
  item->init(scnMgr, name, model, icon, modelType);
  return (item);
}

void	Factory::Client::Element3D::remove(::Element3DContainer *item) {
  pool3DElement->push(item);
}
