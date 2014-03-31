//
// AnnotationBis.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Fri Mar 14 15:11:36 2014 gautier lefebvre
// Last update Wed Mar 26 14:42:39 2014 Gautier Lefebvre
//

#include	"GUIG/AnnotationBis.hpp"
#include	"Kernel/Manager.hpp"
#include	"Converter.hpp"
#include	"Game/Ressources.hpp"
#include	"Game/Controller.hpp"

GUIG::AnnotationBis::AnnotationBis():
  AOverlaySceneManager("GUIG_Annotation_Bis", 1000),
  _gold(0), _food(0), _wood(0), _ress(0),
  _ressType(Kernel::ElementRessources::NONE),
  _bg(NULL),
  _name(NULL), _goldCost(NULL), _foodCost(NULL), _woodCost(NULL), _ressCost(NULL), _coolDown(NULL), _timeCost(NULL), _description(NULL),
  _requirements(),
  _winsize()
{}

GUIG::AnnotationBis::~AnnotationBis() {}

void		GUIG::AnnotationBis::init(unsigned int wx, unsigned int wy) {
  Ogre::Vector2	winsize(wx, wy);
  this->_winsize = Ogre::Vector2(wx, wy);

  this->_bg = this->addOverlayImage(winsize, Ogre::Vector2(200, 300), Ogre::Vector2(0 + this->_x, 0 + this->_y), "annot_bis_bg", "black.png", true);

  this->_goldCost = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 10 + this->_y), "annot_bis_goldcost", "empty.png", "", false);
  this->_goldCost->setColor(Ogre::ColourValue(1, 1, 0));

  this->_woodCost = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 25 + this->_y), "annot_bis_woodcost", "empty.png", "", false);
  this->_woodCost->setColor(Ogre::ColourValue(0, 1, 0));

  this->_foodCost = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 40 + this->_y), "annot_bis_foodcost", "empty.png", "", false);

  this->_ressCost = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 55 + this->_y), "annot_bis_resscost", "empty.png", "", false);
  this->_ressCost->setColor(Ogre::ColourValue(0, 191.0 / 255.0, 1));

  this->_coolDown = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 70 + this->_y), "annot_bis_cooldown", "empty.png", "", false);
  this->_timeCost = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 85 + this->_y), "annot_bis_timecost", "empty.png", "", false);

  this->_description = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 85 + this->_y), "annot_bis_description", "empty.png", "", false);
  this->_name = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 85 + this->_y), "annot_bis_name", "empty.png", "", false);

  draw();
}

void		GUIG::AnnotationBis::draw() {}

void		GUIG::AnnotationBis::clear() {
  for (auto it : this->_requirements) {
    this->delOverlay(it->getName());
  }
  this->_requirements.clear();
  this->setGold(0);
  this->setFood(0);
  this->setWood(0);
  this->setRess(0);
}

void		GUIG::AnnotationBis::updatePositions() {
  unsigned int y = 10;
  const unsigned int leap = 20;

  this->_name->setVisible(true);
  this->_name->updatePosition(Ogre::Vector2(10 + _x, y + _y));
  this->_name->refreshPosition();
  y += leap;

  this->_description->setVisible(true);
  this->_description->updatePosition(Ogre::Vector2(10 + _x, y + _y));
  this->_description->refreshPosition();
  y += leap;

  if (this->_gold != 0) {
    this->_goldCost->setVisible(true);
    this->_goldCost->updatePosition(Ogre::Vector2(10 + _x, y + _y));
    this->_goldCost->refreshPosition();
    y += leap;
  } else {
    this->_goldCost->setVisible(false);
  }

  if (this->_wood != 0) {
    this->_woodCost->setVisible(true);
    this->_woodCost->updatePosition(Ogre::Vector2(10 + _x, y + _y));
    this->_woodCost->refreshPosition();
    y += leap;
  } else {
    this->_woodCost->setVisible(false);
  }

  if (this->_food != 0) {
    this->_foodCost->setVisible(true);
    this->_foodCost->updatePosition(Ogre::Vector2(10 + _x, y + _y));
    this->_foodCost->refreshPosition();
    y += leap;
  } else {
    this->_foodCost->setVisible(false);
  }

  if (this->_ress != 0) {
    this->_ressCost->setVisible(true);
    this->_ressCost->updatePosition(Ogre::Vector2(10 + _x, y + _y));
    this->_ressCost->refreshPosition();
    y += leap;
  } else {
    this->_ressCost->setVisible(false);
  }

  // this->_coolDown->updatePosition(Ogre::Vector2(10 + _x, y + _y));
  // this->_coolDown->refreshPosition();
  // y += leap;
  this->_timeCost->updatePosition(Ogre::Vector2(10 + _x, y + _y));
  this->_timeCost->refreshPosition();
  y += leap;


  for (auto it : this->_requirements) {
    y += leap;
    it->updatePosition(Ogre::Vector2(10 + _x, y + _y));
    it->refreshPosition();
  }
}

void		GUIG::AnnotationBis::setGold(unsigned int v) {
  this->_gold = v;
  this->_goldCost->setText("Gold: " + StringOfUInt(this->_gold));
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setWood(unsigned int v) {
  this->_wood = v;
  this->_woodCost->setText("Wood: " + StringOfUInt(this->_wood));
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setFood(unsigned int v) {
  this->_food = v;
  this->_foodCost->setText("Food: " + StringOfUInt(this->_food));
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setRess(unsigned int v) {
  this->_ress = v;
  this->_ressCost->setText("Ress: " + StringOfUInt(this->_ress));
  this->setRessType(this->_ressType);
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setRessType(Kernel::ElementRessources::Type t) {
  std::string name;

  this->_ressType = t;
  switch (t) {
  case (Kernel::ElementRessources::ENERGY): {
    name = "Energy";
    break ;
  }
  case (Kernel::ElementRessources::MANA): {
    name = "Mana";
    break;
  }
  case (Kernel::ElementRessources::RAGE): {
    name = "Rage";
    break ;
  }
  default : {
    name = "Unknown";
    break ;
  }
  }
  this->_ressCost->setText(name + ": " + StringOfUInt(this->_ress));
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setCoolDown(const std::string &str) {
  this->_coolDown->setText("Cooldown: " +  str);
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::setTime(const std::string &str) {
  this->_timeCost->setText("Creation: " + str);
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::addRequirement(const std::string &requirement, bool fulfilled) {
  Ogre::ColourValue color(0.0, 1.0, 0.0);
  if (!fulfilled) {
    color = Ogre::ColourValue(1.0, 0.0, 0.0);
  }
  OverlayText* text = this->addOverlayText(this->_winsize, Ogre::Vector2(0, 0), Ogre::Vector2(10 + this->_x, 100 +  this->_y), "annot_bis_requirement_" + requirement, "empty.png", requirement, false);
  text->setColor(color);
  this->_requirements.push_back(text);
  updatePositions();
  draw();
}

void		GUIG::AnnotationBis::update(const Kernel::Serial &serial, const Game::Player *player) {
  this->clear();
  const Kernel::Cost *cost = Kernel::Manager::getInstance()->getCost(serial);
  if (cost) {
    this->setGold(cost->ressources.get(Game::Ressources::GOLD));
    this->setWood(cost->ressources.get(Game::Ressources::WOOD));
    this->setFood(cost->ressources.get(Game::Ressources::FOOD));
    this->setRessType(cost->personnalRessource.getRessourceType());
    this->setRess(cost->personnalRessource.getRessource());
  }
  const Kernel::Time *time = Kernel::Manager::getInstance()->getTimer(serial);
  if (time) {
    this->setTime(StringOfDouble(time->creation));
  }

  const Kernel::Data *data = Kernel::Manager::getInstance()->getData(serial);
  if (data) {
    this->_name->setText(data->name);
    this->_description->setText(data->description.length() > 15 ? data->description.substr(15) +  "..." : data->description);

    const std::map<Kernel::Serial, Game::Race *> &races = Game::Controller::getInstance()->getRaces();
    const Game::Requirements *requirements;
    for (auto &race : races) {
      requirements = NULL;
      switch (data->type) {
      case (Game::HERO): {
	if (race.second->hasHero(serial)) {
	  requirements = race.second->getHeroRequirements(serial);
	}
	break ;
      }
      case (Game::UNIT): {
	if (race.second->hasUnit(serial)) {
	  requirements = race.second->getUnitRequirements(serial);
	}
	break ;
      }
      case (Game::BUILDING): {
	if (race.second->hasBuilding(serial)) {
	  requirements = race.second->getBuildingRequirements(serial);
	}
	break ;
      }
      case (Game::AMELIORATION): {
	if (race.second->hasAmelioration(serial)) {
	  requirements = race.second->getAmeliorationRequirements(serial);
	}
	break ;
      }
      }
      if (requirements) {
	const std::map<Kernel::Serial, bool> requ_state = requirements->getFullfilledData(player);
	for (auto &it : requ_state) {
	  const Kernel::Data *data = Kernel::Manager::getInstance()->getData(it.first);
	  if (data) {
	    this->addRequirement(data->name, it.second);
	  }
	}
      }
    }
  }
}
