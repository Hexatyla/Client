// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "GUIG/Profile.hpp"
#include  "utils/convert.hpp"

#ifdef DEBUG_PROFILE
  #define __VISIBLE_PROFILE__ true
#else
  #define __VISIBLE_PROFILE__ false
#endif

GUIG::Profile::Profile():
  AOverlaySceneManager("GUIG_Profile", 10),
  _iconProfil(NULL),
  winsize(0, 0)
{
}

void	GUIG::Profile::init(unsigned int winx, unsigned int winy)
{
  winsize.x = winx;
  winsize.y = winy;
  _ProfilBlank = this->addOverlayImage(winsize, Ogre::Vector2(164, 189), Ogre::Vector2(_x + 36, _y + 36),
      "guigProfile_iconPrincipalBlank", "profil_blank.png", true);
  _PositionProfileIcon = new Ogre::Vector2(37, 12);
  _ProfilBlank->changeZOrder(2);

  _sizeCapacities.x = 65;
  _sizeCapacities.y = 75;
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_0", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(204, 99));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_1", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(271, 99));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_2", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(338, 99));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_3", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(405, 99));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_4", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(171, 156));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_5", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(238, 156));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_6", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(305, 156));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_7", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(372, 156));
  _ImageCapacitiesBlank.push_back(this->addOverlayImage(winsize,
        _sizeCapacities, Ogre::Vector2(_x, _y),
        "guigProfile_capacities_blank_8", "choice_game_type_background.png", true));
   _ImageCapacitiesBlank.back()->changeZOrder(2);
  _PositionCapacities.push_back(new Ogre::Vector2(439, 156));

  _sizeObjects.x = 25;
  _sizeObjects.y = 32;
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_0", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(340, 240));
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_1", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(366, 240));
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_2", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(392, 240));
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_3", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(418, 240));
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_4", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(444, 240));
  _ImageObjectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeObjects, Ogre::Vector2(_x, _y),
        "guigProfile_object_blank_5", "profil_add.png", true));
  _ImageObjectsBlank.back()->changeZOrder(2);
  _PositionObjects.push_back(new Ogre::Vector2(470, 240));

  _sizeEffects.x = 25;
  _sizeEffects.y = 32;
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_0", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(205, 65));
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_1", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(235, 65));
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_2", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(265, 65));
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_3", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(295, 65));
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_4", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(325, 65));
  _ImageEffectsBlank.push_back(this->addOverlayImage(winsize,
        _sizeEffects, Ogre::Vector2(_x, _y),
        "guigProfile_effect_blank_5", "profil_add.png", true));
  _ImageEffectsBlank.back()->changeZOrder(2);
  _PositionEffects.push_back(new Ogre::Vector2(355, 65));

  _sizeProductions.x = 25;
  _sizeProductions.y = 32;
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
        _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_0", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(24, 26));
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
         _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_1", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(11, 53));
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
         _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_2", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(11, 130));
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
         _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_3", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(24, 155));
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
         _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_4", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(92, 195));
  _ImageProductionsBlank.push_back(this->addOverlayImage(winsize,
         _sizeProductions, Ogre::Vector2(_x, _y),
        "guigProfile_production_blank_5", "profil_add.png", true));
  _ImageProductionsBlank.back()->changeZOrder(2);
  _PositionProductions.push_back(new Ogre::Vector2(118, 195));
}

GUIG::Profile::~Profile()
{
}

void  GUIG::Profile::deleteGraphicalItem(const GUIG::Profile::VectorKernel &vk, unsigned int pos, const std::string &name)
{
  AOverlay    *ptr = NULL;
  std::string fileName = "guigProfile_" + name + "_" + vk.serial + "_" + toString(pos);

  ptr = dynamic_cast<AOverlay*>(this->getOverlay(fileName));
  std::cout << "TRY CLEAR ::" << name << std::endl;
  if (ptr == NULL)
    return;
  if (name == "profile")
    std::cout << "CLEAR PROFILE" << std::endl;
  ptr->setVisible(false);
}

void  GUIG::Profile::CreateAndPosItem(const GUIG::Profile::VectorKernel &vk, const Ogre::Vector2 &pos,
                                      const Ogre::Vector2 &size, const std::string &name, unsigned int posV)
{
  Button    *ptr = NULL;
  std::string fileName = "guigProfile_" + name + "_" + vk.serial + "_" + toString(posV);

  ptr = dynamic_cast<Button*>(this->getOverlay(fileName));
  if (ptr == NULL)
  {
    ptr = this->addButton(winsize, size, Ogre::Vector2(_x, _y),
                          fileName,  vk.pathImage);
    if (ptr == NULL)
    {
      std::cout << "BIG ERROR" << std::endl;
      return;
    }
    ptr->changeZOrder(2);
  }
  ptr->updatePosition(Ogre::Vector2(pos.x + _x, pos.y + _y));
  ptr->setVisible(true);
  std::cout << "createAndPos :" << name << " [" << fileName << "]"<< std::endl;
}

void	GUIG::Profile::draw()
{
  for (unsigned int i = 0; (i < _ImageCapacitiesBlank.size() || i < _capacities.size()) && i < 9; ++i)
  {
    if (i < _capacities.size())
    {
      _ImageCapacitiesBlank[i]->setVisible(false);
      CreateAndPosItem(*(_capacities[i]), *(_PositionCapacities[i]), _sizeCapacities, "capacities", i);
    }
    else
    {
      if (_ImageCapacitiesBlank[i])
      {
        _ImageCapacitiesBlank[i]->setVisible(true);
        _ImageCapacitiesBlank[i]->updatePosition(_PositionCapacities[i]->x + _x, _PositionCapacities[i]->y + _y);
      }
    }
  }

  for (unsigned int i = 0; (i < _ImageObjectsBlank.size() || i < _objects.size()) && i < 6; ++i)
  {
    if (i < _objects.size())
    {
      _ImageObjectsBlank[i]->setVisible(false);
      CreateAndPosItem(*(_objects[i]), *(_PositionObjects[i]), _sizeObjects, "objects", i);
    }
    else
    {
      if (_ImageObjectsBlank[i])
        if (__VISIBLE_PROFILE__)
        {
          _ImageObjectsBlank[i]->setVisible(true);
          _ImageObjectsBlank[i]->updatePosition(_PositionObjects[i]->x + _x, _PositionObjects[i]->y + _y);
        }
        else
          _ImageObjectsBlank[i]->setVisible(false);
    }
  }

  for (unsigned int i = 0; (i < _productions.size() || i < _ImageProductionsBlank.size()) && i < 6; ++i)
  {
    if (i < _productions.size())
    {
      // produc reel
      _ImageProductionsBlank[i]->setVisible(false);
      CreateAndPosItem(*(_productions[i]), *(_PositionProductions[i]), _sizeProductions, "productions", i);
    }
    else
    {
      if (_PositionProductions[i])
        if (__VISIBLE_PROFILE__)
        {
          _ImageProductionsBlank[i]->setVisible(true);
          _ImageProductionsBlank[i]->updatePosition(_PositionProductions[i]->x + _x, _PositionProductions[i]->y + _y);
        }
        else
          _ImageProductionsBlank[i]->setVisible(false);
    }
  }

  for (unsigned int i = 0; (i < _ImageEffectsBlank.size() || i < _effects.size()) && i < 6; ++i)
  {
    if (i < _effects.size())
    {
      // effect reel
      _ImageEffectsBlank[i]->setVisible(false);
      CreateAndPosItem(*(_effects[i]), *(_PositionEffects[i]), _sizeEffects, "effects", i);
    }
    else
    {
      if (_ImageEffectsBlank[i])
        if (__VISIBLE_PROFILE__)
        {
          _ImageEffectsBlank[i]->setVisible(true);
          _ImageEffectsBlank[i]->updatePosition(_PositionEffects[i]->x + _x, _PositionEffects[i]->y + _y);
        }
        else
          _ImageEffectsBlank[i]->setVisible(false);
    }
  }

  if (_iconProfil == NULL)
  {
    _ProfilBlank->updatePosition(_PositionProfileIcon->x + _x, _PositionProfileIcon->y + _y);
    _ProfilBlank->setVisible(true);
  }
  else
  {
    _ProfilBlank->setVisible(false);
    CreateAndPosItem(*(_iconProfil), Ogre::Vector2(_PositionProfileIcon->x, _PositionProfileIcon->y),
                      Ogre::Vector2(164, 189), "profile", 0);
  }
}

void  GUIG::Profile::clear()
{
  clearProductions();
  clearObjects();
  clearCapacities();
  clearEffects();
  clearIcons();
}

void  GUIG::Profile::clearProductions()
{
  while (_productions.size() > 0)
    productionsElementPop();
}

void  GUIG::Profile::clearObjects()
{
  while (_objects.size() > 0)
    objectsElementPop();
}

void  GUIG::Profile::clearCapacities()
{
  while (_capacities.size() > 0)
    capacitiesElementPop();
}

void  GUIG::Profile::clearEffects()
{
  while (_effects.size() > 0)
    effectsElementPop();
}

void  GUIG::Profile::clearIcons()
{
  if (_iconProfil != NULL)
    deleteGraphicalItem(*(_iconProfil), 0, "profile");
}

void  GUIG::Profile::profileSetIcon(const std::string &file, Kernel::ID::id_t id, const Kernel::Serial &serial)
{
  clearIcons();
  _iconProfil = new VectorKernel;
  _iconProfil->serial = serial;
  _iconProfil->id = id;
  _iconProfil->pathImage = file;
}

// Production gestion
void  GUIG::Profile::productionsElementPush(Kernel::ID::id_t id, const Kernel::Serial &serial, const std::string &img)
{
  if (_productions.size() >= 6)
    return;
  GUIG::Profile::VectorKernel *s = new GUIG::Profile::VectorKernel;
  s->serial = serial;
  s->id = id;
  s->pathImage = img;
  _productions.push_back(s);
  draw();
}

bool  GUIG::Profile::productionsElementPop()
{
  if (_productions.size() <= 0)
    return (false);
  VectorKernel *s = _productions.back();
  deleteGraphicalItem(*(_productions[_productions.size() - 1]), _productions.size() - 1, "productions");
  _productions.pop_back();
  delete s;
  return (true);
}

void  GUIG::Profile::productionsElementDelete(Kernel::ID::id_t id)
{
  if (_productions.size() <= 0)
    return;
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _productions.size())
  {
    if (_productions[i]->id == id)
      break;
    i++;
  }
  if (i >= _productions.size())
    return;
  s = _productions[i];
  deleteGraphicalItem(*(s), i, "productions");
  _productions.erase(_productions.begin() + i);
  delete s;
}

bool  GUIG::Profile::productionsElementDelete(const Kernel::Serial &serial)
{
  if (_productions.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _productions.size())
  {
    if (_productions[i]->serial == serial)
      break;
    i++;
  }
  if (i >= _productions.size())
    return (false);
  s = _productions[i];
  deleteGraphicalItem(*(_productions[i]), i, "productions");
  _productions.erase(_productions.begin() + i);
  delete s;
  return (true);
}

void  GUIG::Profile::productionsElementDeleteAll(const Kernel::Serial &serial)
{
  if (productionsElementDelete(serial))
    productionsElementDeleteAll(serial);
}

void  GUIG::Profile::productionsElementDeleteAt(unsigned int i)
{
  if (i >= _productions.size())
    return;
  GUIG::Profile::VectorKernel *s = _productions[i];
  deleteGraphicalItem(*(_productions[i]), i, "productions");
  _productions.erase(_productions.begin() + i);
  delete s;
}

Kernel::Serial*  GUIG::Profile::getSerialToProductionElement(unsigned int id)
{
  if (id < _productions.size())
    return &(_productions[id]->serial);
  return (NULL);
}

Kernel::ID::id_t*  GUIG::Profile::getIdToProductionElement(unsigned int id)
{
  if (id < _productions.size())
    return &(_productions[id]->id);
  return (NULL);
}

unsigned int GUIG::Profile::getProductionsSize()
{
  return (_productions.size());
}

// object gestion
void  GUIG::Profile::objectsElementPush(Kernel::ID::id_t id, const Kernel::Serial &serial, const std::string &img)
{
  GUIG::Profile::VectorKernel *s = new GUIG::Profile::VectorKernel;
  if (_objects.size() >= 6)
     return;
  s->serial = serial;
  s->id = id;
  s->pathImage = img;
  _objects.push_back(s);
  draw();
}

bool  GUIG::Profile::objectsElementPop()
{
  if (_objects.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = _objects.back();
  deleteGraphicalItem(*(_objects[_objects.size() - 1]), _objects.size() - 1, "objects");
  _objects.pop_back();
  delete s;
  return (true);
}

void  GUIG::Profile::objectsElementDelete(Kernel::ID::id_t id)
{
  if (_objects.size() <= 0)
    return;
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _objects.size())
  {
    if (_objects[i]->id == id)
      break;
    i++;
  }
  if (i >= _objects.size())
    return;
  s = _objects[i];
  deleteGraphicalItem(*(_objects[i]), i, "objects");
  _objects.erase(_objects.begin() + i);
  delete s;
}

bool  GUIG::Profile::objectsElementDelete(const Kernel::Serial &serial)
{
  if (_objects.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _objects.size())
  {
    if (_objects[i]->serial == serial)
      break;
    i++;
  }
  if (i >= _objects.size())
    return (false);
  s = _objects[i];
  deleteGraphicalItem(*(_objects[i]), i, "objects");
  _objects.erase(_objects.begin() + i);
  delete s;
  return (true);
}

void  GUIG::Profile::objectsElementDeleteAll(const Kernel::Serial &serial)
{
  if (objectsElementDelete(serial))
    objectsElementDeleteAll(serial);
}

void  GUIG::Profile::objectsElementDeleteAt(unsigned int i)
{
  if (i >= _objects.size())
    return;
  GUIG::Profile::VectorKernel *s = _objects[i];
  deleteGraphicalItem(*(_objects[i]), i, "objects");
  _objects.erase(_objects.begin() + i);
  delete s;
}

Kernel::Serial  *GUIG::Profile::getSerialToObjectElement(unsigned int id)
{
  if (id < _objects.size())
    return &(_objects[id]->serial);
  return (NULL);
}

Kernel::ID::id_t      *GUIG::Profile::getIdToObjectElement(unsigned int id)
{
  if (id < _objects.size())
    return &(_objects[id]->id);
  return (NULL);
}

unsigned int GUIG::Profile::getObjectsSize()
{
  return (_objects.size());
}

// Capacities gestion
void  GUIG::Profile::capacitiesElementPush(Kernel::ID::id_t id, const Kernel::Serial &serial, const std::string &img)
{
  if (_capacities.size() >= 9)
    return;
  GUIG::Profile::VectorKernel *s = new VectorKernel;
  s->serial = serial;
  s->id = id;
  s->pathImage = img;
  _capacities.push_back(s);
  draw();
}

bool  GUIG::Profile::capacitiesElementPop()
{
  if (_capacities.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = _capacities.back();
  deleteGraphicalItem(*(_capacities[_capacities.size() - 1]), _capacities.size() - 1, "capacities");
  _capacities.pop_back();
  delete s;
  return (true);
}

void  GUIG::Profile::capacitiesElementDelete(Kernel::ID::id_t id)
{
  if (_capacities.size() <= 0)
    return;
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _capacities.size())
  {
    if (_capacities[i]->id == id)
      break;
    i++;
  }
  if (i >= _capacities.size())
    return;
  s = _capacities[i];
  deleteGraphicalItem(*(_capacities[i]), i, "capacities");
  _capacities.erase(_capacities.begin() + i);
  delete s;
}

bool  GUIG::Profile::capacitiesElementDelete(const Kernel::Serial &serial)
{
  if (_capacities.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _capacities.size())
  {
    if (_capacities[i]->serial == serial)
      break;
    i++;
  }
  if (i >= _capacities.size())
    return (false);
  s = _capacities[i];
  deleteGraphicalItem(*(_capacities[i]), i, "capacities");
  _capacities.erase(_capacities.begin() + i);
  delete s;
  return (true);
}

void  GUIG::Profile::capacitiesElementDeleteAll(const Kernel::Serial &serial)
{
  if (capacitiesElementDelete(serial))
    capacitiesElementDeleteAll(serial);
}

void  GUIG::Profile::capacitiesElementDeleteAt(unsigned int i)
{
  if (i >= _capacities.size())
    return;
  GUIG::Profile::VectorKernel *s = _capacities[i];
  deleteGraphicalItem(*(_capacities[i]), i, "capacities");
  _capacities.erase(_capacities.begin() + i);
  delete s;
}

Kernel::Serial  *GUIG::Profile::getSerialToCapacityElement(unsigned int id)
{
  if (id < _capacities.size())
    return &(_capacities[id]->serial);
  return (NULL);
}

Kernel::ID::id_t      *GUIG::Profile::getIdToCapacityElement(unsigned int id)
{
  if (id < _capacities.size())
    return &(_capacities[id]->id);
  return (NULL);
}

unsigned int GUIG::Profile::getCapacitiesSize()
{
  return (_capacities.size());
}

// Effects gestion
void  GUIG::Profile::effectsElementPush(Kernel::ID::id_t id, const Kernel::Serial &serial, const std::string &img)
{
  if (_effects.size() >= 6)
    return;
  GUIG::Profile::VectorKernel *s = new GUIG::Profile::VectorKernel;
  s->serial = serial;
  s->id = id;
  s->pathImage = img;
  _effects.push_back(s);
  draw();
}

bool  GUIG::Profile::effectsElementPop()
{
  if (_effects.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = _effects.back();
  deleteGraphicalItem(*(_effects[_effects.size() - 1]), _effects.size() - 1, "effects");
  _effects.pop_back();
  delete s;
  return (true);
}

void  GUIG::Profile::effectsElementDelete(Kernel::ID::id_t id)
{
  if (_effects.size() <= 0)
    return;
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _effects.size())
  {
    if (_effects[i]->id == id)
      break;
    i++;
  }
  if (i >= _effects.size())
    return;
  s = _effects[i];
  deleteGraphicalItem(*(_effects[i]), i, "effects");
  _effects.erase(_effects.begin() + i);
  delete s;
}

bool  GUIG::Profile::effectsElementDelete(const Kernel::Serial &serial)
{
  if (_effects.size() <= 0)
    return (false);
  GUIG::Profile::VectorKernel *s = NULL;
  unsigned int i = 0;
  while (i < _effects.size())
  {
    if (_effects[i]->serial == serial)
      break;
    i++;
  }
  if (i >= _effects.size())
    return (false);
  s = _effects[i];
  deleteGraphicalItem(*(_effects[i]), i, "effects");
  _effects.erase(_effects.begin() + i);
  delete s;
  return (true);
}

void  GUIG::Profile::effectsElementDeleteAll(const Kernel::Serial &serial)
{
  if (effectsElementDelete(serial))
    effectsElementDeleteAll(serial);
}

void  GUIG::Profile::effectsElementDeleteAt(unsigned int i)
{
  if (i >= _effects.size())
    return;
  GUIG::Profile::VectorKernel *s = _effects[i];
  deleteGraphicalItem(*(_effects[i]), i, "effects");
  _effects.erase(_effects.begin() + i);
  delete s;
}

Kernel::Serial  *GUIG::Profile::getSerialToEffectElement(unsigned int id)
{
  if (id < _effects.size())
    return &(_effects[id]->serial);
  return (NULL);
}

Kernel::ID::id_t      *GUIG::Profile::getIdToEffectElement(unsigned int id)
{
  if (id < _effects.size())
    return &(_effects[id]->id);
  return (NULL);
}

unsigned int GUIG::Profile::getEffectsSize()
{
  return (_effects.size());
}
