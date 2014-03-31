//
// Squad.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Wed Mar 19 14:10:11 2014 gautier lefebvre
// Last update Tue Mar 25 16:16:49 2014 Gautier Lefebvre
//

#include	"GUIG/Squad.hpp"
#include	"Converter.hpp"
#include	"Logger.hpp"

GUIG::Squad::unitInfo::unitInfo():
  unit(NULL),
  background(NULL),
  id(0),
  image(""),
  life(0),
  serial("")
{}

GUIG::Squad::Squad():
  AOverlaySceneManager("GUIG_Squad", 10),
  _actions(5, NULL),
  _unitsBlank(12, NULL),
  _units(12)
{}

GUIG::Squad::~Squad() {}

void	GUIG::Squad::draw() {}

void	GUIG::Squad::init(unsigned int wx, unsigned int wy) {
  this->_winsize = Ogre::Vector2(wx, wy);

  this->_actions[0] = this->addButton(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(102 + _x, 0 + _y), "guigSquad_round", "round.png", true);
  this->_actions[1] = this->addButton(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(170 + _x, 0 + _y), "guigSquad_shield" , "defensive.png", true);
  this->_actions[2] = this->addButton(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(238 + _x, 0 + _y), "guigSquad_attack", "attack.png", true);
  this->_actions[3] = this->addButton(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(306 + _x, 0 + _y), "guigSquad_alert", "alert.png", true);
  this->_actions[4] = this->addButton(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(374 + _x, 120 + _y), "guigSquad_cancel", "close_core.png", true);

  this->_unitsBlank[0] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(34 + _x, 0 + _y), "guigSquad_unitsbg_1", "choice_game_type_background.png", true);
  this->_unitsBlank[1] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(0 + _x, 60 + _y), "guigSquad_unitsbg_2", "choice_game_type_background.png", true);
  this->_unitsBlank[2] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(68 + _x, 60 + _y), "guigSquad_unitsbg_3", "choice_game_type_background.png", true);
  this->_unitsBlank[3] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(136 + _x, 60 + _y), "guigSquad_unitsbg_4", "choice_game_type_background.png", true);
  this->_unitsBlank[4] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(204 + _x, 60 + _y), "guigSquad_unitsbg_5", "choice_game_type_background.png", true);
  this->_unitsBlank[5] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(272 + _x, 60 + _y), "guigSquad_unitsbg_6", "choice_game_type_background.png", true);
  this->_unitsBlank[6] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(340 + _x, 60 + _y), "guigSquad_unitsbg_7", "choice_game_type_background.png", true);
  this->_unitsBlank[7] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(34 + _x, 120 + _y), "guigSquad_unitsbg_8", "choice_game_type_background.png", true);
  this->_unitsBlank[8] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(102 + _x, 120 + _y), "guigSquad_unitsbg_9", "choice_game_type_background.png", true);
  this->_unitsBlank[9] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(170 + _x, 120 + _y), "guigSquad_unitsbg_10", "choice_game_type_background.png", true);
  this->_unitsBlank[10] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(238 + _x, 120 + _y), "guigSquad_unitsbg_11", "choice_game_type_background.png", true);
  this->_unitsBlank[11] = this->addOverlayImage(_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(306 + _x, 120 + _y), "guigSquad_unitsbg_12", "choice_game_type_background.png", true);

  draw();
}

void	GUIG::Squad::definePosition(unsigned int c, int &x, int &y) const {
  switch (c) {
  case (1): {
    x = 34 + _x; y = 0 + _y; break ;
  }
  case (2): {
    x = 0 + _x; y = 60 + _y; break ;
  }
  case (3): {
    x = 68 + _x; y = 60 + _y; break ;
  }
  case (4): {
    x = 136 + _x; y = 60 + _y; break ;
  }
  case (5): {
    x = 204 + _x; y = 60 + _y; break ;
  }
  case (6): {
    x = 272 + _x; y = 60 + _y; break ;
  }
  case (7): {
    x = 340 + _x; y = 60 + _y; break ;
  }
  case (8): {
    x = 34 + _x; y = 120 + _y; break ;
  }
  case (9): {
    x = 102 + _x; y = 120 + _y; break ;
  }
  case (10): {
    x = 170 + _x; y = 120 + _y; break ;
  }
  case (11): {
    x = 238 + _x; y = 120 + _y; break ;
  }
  case (12): {
    x = 306 + _x; y = 120 + _y; break ;
  }
  default: {
    break ;
  }
  }
}

std::string	GUIG::Squad::defineButtonName(const Kernel::Serial &serial, unsigned int c) const {
  return ("Squad_element_" + serial + "_" + StringOfUInt(c));
}

std::string	GUIG::Squad::defineBackgroundName(unsigned int c, unsigned int life, std::string &path) const {
  if (75 < life) {
    path = "unit_100.png";
    return ("Squad_life_" + StringOfUInt(c) + "_100");
  }
  else if (50 < life && life <= 75) {
    path = "unit_75.png";
    return ("Squad_life_" + StringOfUInt(c) + "_75");
  }
  else if (25 < life && life <= 50) {
    path = "unit_25.png";
    return ("Squad_life_" + StringOfUInt(c) + "_25");
  }
  else {
    path = "unit_5.png";
    return ("Squad_life_" + StringOfUInt(c) + "_5");
  }
}

unsigned int GUIG::Squad::getCaseByID(Kernel::ID::id_t id) const {
  unsigned int i = 1;
  for (auto &it : this->_units) {
    if (it.id == id) {
      return (i);
    }
    ++i;
  }
  return (0);
}

void	GUIG::Squad::setUnit(unsigned int c, const std::string &image, Kernel::ID::id_t id, const Kernel::Serial& serial) {
  std::string name = this->defineButtonName(serial, c);
  std::string path;
  std::string bgname = this->defineBackgroundName(c, 100, path);

  AOverlay *unit = this->getOverlay(name);
  AOverlay *bg = this->getOverlay(bgname);
  int x, y;
  this->definePosition(c, x, y);
  if (!unit) {
    unit = this->addButton(this->_winsize, Ogre::Vector2(60, 71), Ogre::Vector2(x + 2, y + 2), name, image);
    unit->changeZOrder(11);
  }
  if (!bg) {
    bg = this->addButton(this->_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(x, y), bgname, path);
    bg->changeZOrder(10);
  }

  if (this->_units[c - 1].background) {
    this->_units[c - 1].background->setVisible(false);
  }
  this->_units[c-1].background = bg;
  bg->setVisible(true);

  if (this->_units[c - 1].unit) {
    this->_units[c - 1].unit->setVisible(false);
  }
  this->_units[c - 1].unit = unit;
  this->_units[c - 1].id = id;
  this->_units[c - 1].image = image;
  this->_units[c - 1].life = 100;
  this->_units[c - 1].serial = serial;
  unit->setVisible(true);

  this->_unitsBlank[c - 1]->setVisible(false);
  draw();
}

void		GUIG::Squad::setLife(Kernel::ID::id_t id, unsigned int life) {
  unsigned int c = getCaseByID(id);
  if (c == 0) { return ; }

  std::string img;
  std::string bgname = defineBackgroundName(c, life, img);
  AOverlay *bg = getOverlay(bgname);
  int x, y;
  this->definePosition(c, x, y);

  if (!bg) {
    bg = this->addButton(this->_winsize, Ogre::Vector2(64, 75), Ogre::Vector2(x, y), bgname, img);
    bg->changeZOrder(10);
  }

  if (this->_units[c - 1].background) {
    this->_units[c - 1].background->setVisible(false);
  }
  this->_units[c-1].background = bg;
  this->_units[c-1].life = life;
  bg->setVisible(true);
  draw();
}

void		GUIG::Squad::emptyCase(unsigned int tmp) {
  if (_units[tmp-1].unit) {
    _units[tmp-1].unit->setVisible(false);
  }
  if (_units[tmp-1].background) {
    _units[tmp-1].background->setVisible(false);
  }
  _unitsBlank[tmp-1]->setVisible(true);
  _units[tmp-1].unit = NULL;
  _units[tmp-1].background = NULL;
  _units[tmp-1].id = 0;
  _units[tmp-1].image = "";
  _units[tmp-1].life = 0;
  _units[tmp-1].serial = "";
  draw();
}

void		GUIG::Squad::updatePositions() {
  for (unsigned int c = 0 ; c < 12 ; ++c) {
    if (c < 11 && _units[c].unit == NULL) {
      for (unsigned int tmp = c + 1 ; tmp < 12 ; ++tmp) {
	if (_units[tmp].unit != NULL) {
	  this->setUnit(c + 1, _units[tmp].image, _units[tmp].id, _units[tmp].serial);
	  this->setLife(_units[tmp].id, _units[tmp].life);
	  emptyCase(tmp + 1);
	  break ;
	}
      }
    }
  }
  draw();
}

bool		GUIG::Squad::addUnit(const std::string &img, Kernel::ID::id_t id, const Kernel::Serial &serial) {
  for (unsigned int c = 0 ; c < 12 ; ++c) {
    if (_units[c].unit != NULL && _units[c].id == id) {
      return (false);
    }
  }
  for (unsigned int c = 0 ; c < 12 ; ++c) {
    if (_units[c].unit == NULL) {
      setUnit(c + 1, img, id, serial);
      updatePositions();
      return (true);
    }
  }
  return (false);
}

void		GUIG::Squad::removeUnit(Kernel::ID::id_t id) {
  unsigned int c = getCaseByID(id);
  if (c == 0) 
    return;
  emptyCase(c);
  updatePositions();
}

Kernel::ID::id_t	GUIG::Squad::getIdOfCase(unsigned int c) {
  return (_units[c - 1].id);
}

void  GUIG::Squad::clear()
{
  get_idUnits();
  for (unsigned int i = 0; i < _idUnits.size(); ++i)
    removeUnit(_idUnits[i]);
  _idUnits.clear();
}

const std::vector<Kernel::ID::id_t> &GUIG::Squad::get_idUnits()
{
  _idUnits.clear();
  for (unsigned int i = 0; i < _units.size(); ++i)
  {
    if (_units[i].unit == NULL)
      break;
    _idUnits.push_back(_units[i].id);
  }
  return (_idUnits);
}

void		GUIG::Squad::update(const std::map<Kernel::ID::id_t, Game::AElement *> &elements) {
  for (auto it : this->get_idUnits()) {
    try {
      const Game::AElement *element = elements.at(it);
      this->setLife(it, static_cast<unsigned int>(static_cast<double>(element->getCurrentLife() * 100) / static_cast<double>(element->getMaxLife())));
    }
    catch (const std::out_of_range&) {}
  }
}
