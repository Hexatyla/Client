//
// Annotation.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Thu Mar 13 14:56:54 2014 gautier lefebvre
// Last update Tue Mar 25 16:53:07 2014 Gautier Lefebvre
//

#include	"Converter.hpp"
#include	"GUIG/Annotation.hpp"
#include	"Game/Unit.hpp"
#include	"Game/Building.hpp"
#include	"Game/RessourcesSpot.hpp"

GUIG::Annotation::Annotation():
  AOverlaySceneManager("GUIG_Annotation", 10),
  _name(""),
  _speed(0),
  _range(0), _rangeBonus(0),
  _attack(0), _attackBonus(0),
  _armor(0), _armorBonus(0),
  _hp(0),
  _hpmax(0), _hpmaxBonus(0),
  _ress(0),
  _elementType(Kernel::ElementRessources::NONE),
  _bg(NULL), _shield(NULL), _gun(NULL),
  _nameText(NULL),
  _speedText(NULL),
  _rangeText(NULL),
  _attackText(NULL),
  _armorText(NULL),
  _hpText(NULL),
  _ressText(NULL),
  _ressourcesCarryText(NULL),
  _description(NULL),
  _building(NULL)
{}

GUIG::Annotation::~Annotation() {}

void		GUIG::Annotation::init(unsigned int winx, unsigned int winy) {
  Ogre::Vector2 winsize(winx, winy);

  this->setRelatifPosition(this->_x, this->_y);
  this->_bg = this->addOverlayImage(winsize, Ogre::Vector2(275, 280), Ogre::Vector2(0 + this->_x, 0 + this->_y), "annot_bg", "annotation_background.png" , true);
  this->_bg->setOpacity(0.8);
  this->_shield = this->addOverlayImage(winsize, Ogre::Vector2(40, 40), Ogre::Vector2(20 + this->_x, 132 + this->_y), "annot_shield", "shield.png", true);
  this->_gun = this->addOverlayImage(winsize, Ogre::Vector2(50, 50), Ogre::Vector2(10 + this->_x, 52 + this->_y), "annot_gun", "gun.png", true);

  this->_nameText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 10 + this->_y), "annot_name_text", "empty.png", "McFarmer", false);
  this->_speedText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 45 + this->_y), "annot_speed_text", "empty.png", "Normal", false);
  this->_rangeText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 65 + this->_y), "annot_range_text", "empty.png", "0", false);
  this->_attackText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 85 + this->_y), "annot_attack_text", "empty.png", "0", false);
  this->_armorText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 120 + this->_y), "annot_armor_text", "empty.png", "0", false);
  this->_hpText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 140 + this->_y), "annot_hp_text", "empty.png", "0/0", false);
  this->_ressText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + this->_x, 160 + this->_y), "annot_ress_text", "empty.png", "", false);
  this->_ressourcesCarryText = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + _x, 200 + this->_y), "annot_ressourcesscarry_text", "empty.png", "", false);
  this->_description = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(5 + _x, 240 + this->_y), "annot_description_text", "empty.png", "", false);
  this->_building = this->addOverlayText(winsize, Ogre::Vector2(0, 0), Ogre::Vector2(75 + _x, 27 + _y), "annot_building_text", "empty.png", "en construction...", false);
  this->_building->setColor(Ogre::ColourValue(1, 0, 0));

  this->setVisible(false);

  this->draw();
}

void		GUIG::Annotation::draw() {}

void		GUIG::Annotation::setName(const std::string &name) {
  this->_name = name;
  this->_nameText->setText(name);
  this->draw();
}

void		GUIG::Annotation::setSpeed(unsigned int v) {
  this->_speed = v;
  if (0 < v && v < 20) {
    this->_speedText->setText("Slow");
  } else if (20 < v && v < 30) {
    this->_speedText->setText("Normal");
  } else {
    this->_speedText->setText("Fast");
  }
  this->draw();
}

void		GUIG::Annotation::addBonus(std::string &str, Ogre::ColourValue& color, int bonus, const std::string &bonusstr) const {
  color = Ogre::ColourValue(1, 1, 1);
  if (bonus != 0) {
    str += " (";
    if (bonus > 0) {
      color = Ogre::ColourValue(0, 1, 0);
      str += "+" + bonusstr;
    }
    else {
      color = Ogre::ColourValue(1, 0, 0);
      str += bonusstr;
    }
    str += ")";
  }
}

void		GUIG::Annotation::setRange(double v) {
  this->_range = v;
  std::string text("Range: " + StringOfDouble(this->_range + this->_rangeBonus));
  Ogre::ColourValue color;

  int val = 0;
  if (this->_rangeBonus > 0.0) {
    val = 1;
  } else if (this->_rangeBonus < 0.0) {
    val = -1;
  }

  this->addBonus(text, color, val, StringOfDouble(this->_rangeBonus));
  this->_rangeText->setText(text);
  this->_rangeText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setRangeBonus(double v) {
  this->_rangeBonus = v;
  std::string text("Range: " + StringOfDouble(this->_range + this->_rangeBonus));
  Ogre::ColourValue color;

  int val = 0;
  if (v > 0.0) { val = 1; }
  else if (v < 0.0) { val = -1; }

  this->addBonus(text, color, val, StringOfDouble(this->_rangeBonus));
  this->_rangeText->setText(text);
  this->_rangeText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setAttack(unsigned int v) {
  this->_attack = v;
  std::string text("Attack: " + StringOfUInt(this->_attack + this->_attackBonus));
  Ogre::ColourValue color;

  int val = (this->_attackBonus == 0 ? 0 : (this->_attackBonus > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_attackBonus));
  this->_attackText->setText(text);
  this->_attackText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setAttackBonus(int v) {
  this->_attackBonus = v;
  std::string text("Attack: " + StringOfUInt(this->_attack + this->_attackBonus));
  Ogre::ColourValue color;

  int val = (v == 0 ? 0 : (v > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_attackBonus));
  this->_attackText->setText(text);
  this->_attackText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setArmor(unsigned int v) {
  this->_armor = v;
  std::string text("Armor: " + StringOfUInt(this->_armor + this->_armorBonus));
  Ogre::ColourValue color;

  int val = (this->_armorBonus == 0 ? 0 : (this->_armorBonus > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_armorBonus));
  this->_armorText->setText(text);
  this->_armorText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setArmorBonus(int v) {
  this->_armorBonus = v;
  std::string text("Armor: " + StringOfUInt(this->_armor + this->_armorBonus));
  Ogre::ColourValue color;

  int val = (v == 0 ? 0 : (v > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_armorBonus));
  this->_armorText->setText(text);
  this->_armorText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setHP(unsigned int v) {
  this->_hp = v;
  std::string text("HP: " + StringOfUInt(this->_hp) + "/" + StringOfUInt(this->_hpmax + this->_hpmaxBonus));
  Ogre::ColourValue color;

  int val = (this->_hpmaxBonus == 0 ? 0 : (this->_hpmaxBonus > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfUInt(this->_hpmaxBonus));
  this->_hpText->setText(text);
  if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 1.0/4.0) {
    color = Ogre::ColourValue(1, 0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 2.0/4.0) {
    color = Ogre::ColourValue(1, 165.0/255.0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 3.0/4.0) {
    color = Ogre::ColourValue(1, 1, 0);
  }
  else {
    color = Ogre::ColourValue(0, 1, 0);
  }
  this->_hpText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setHPMax(unsigned int v) {
  this->_hpmax = v;
  std::string text("HP: " + StringOfUInt(this->_hp) + "/" + StringOfUInt(this->_hpmax + this->_hpmaxBonus));
  Ogre::ColourValue color;

  int val = (this->_hpmaxBonus == 0 ? 0 : (this->_hpmaxBonus > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_hpmaxBonus));
  this->_hpText->setText(text);
  if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 1.0/4.0) {
    color = Ogre::ColourValue(1, 0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 2.0/4.0) {
    color = Ogre::ColourValue(1, 165.0/255.0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 3.0/4.0) {
    color = Ogre::ColourValue(1, 1, 0);
  }
  else {
    color = Ogre::ColourValue(0, 1, 0);
  }
  this->_hpText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setHPMaxBonus(int v) {
  this->_hpmaxBonus = v;
  std::string text("HP: " + StringOfUInt(this->_hp) + "/" + StringOfUInt(this->_hpmax + this->_hpmaxBonus));
  Ogre::ColourValue color;

  int val = (v == 0 ? 0 : (v > 0 ? 1 : -1));

  this->addBonus(text, color, val, StringOfInt(this->_hpmaxBonus));
  this->_hpText->setText(text);
  if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 1.0/4.0) {
    color = Ogre::ColourValue(1, 0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 2.0/4.0) {
    color = Ogre::ColourValue(1, 165.0/255.0, 0);
  }
  else if (static_cast<float>(this->_hp) / static_cast<float>(this->_hpmax + this->_hpmaxBonus) < 3.0/4.0) {
    color = Ogre::ColourValue(1, 1, 0);
  }
  else {
    color = Ogre::ColourValue(0, 1, 0);
  }
  this->_hpText->setColor(color);
  this->draw();
}

void		GUIG::Annotation::setRess(unsigned int v) {
  this->_ress = v;
  std::string text("Ressource: " + StringOfUInt(this->_ress));
  Ogre::ColourValue color(1, 1, 1);

  this->_ressText->setText(text);
  this->_ressText->setColor(color);
  this->setRessType(this->_elementType);
  if (v == 0) {
    this->_ressText->setVisible(false);
  }
  else {
    this->_ressText->setVisible(true);
  }
  this->draw();
}

void		GUIG::Annotation::setRessType(Kernel::ElementRessources::Type t) {
  this->_elementType = t;
  std::string name;

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
  this->_ressText->setText(name + ": " + StringOfUInt(this->_ress));
  draw();
}

void	GUIG::Annotation::hideAll() {
  this->_shield->setVisible(false);
  this->_gun->setVisible(false);
  this->_nameText->setVisible(false);
  this->_speedText->setVisible(false);
  this->_rangeText->setVisible(false);
  this->_attackText->setVisible(false);
  this->_armorText->setVisible(false);
  this->_hpText->setVisible(false);
  this->_ressText->setVisible(false);
  this->_ressourcesCarryText->setVisible(false);
  this->_description->setVisible(false);
  this->_building->setVisible(false);
}

void	GUIG::Annotation::showAll() {
  this->_shield->setVisible(true);
  this->_gun->setVisible(true);
  this->_nameText->setVisible(true);
  this->_speedText->setVisible(true);
  this->_rangeText->setVisible(true);
  this->_attackText->setVisible(true);
  this->_armorText->setVisible(true);
  this->_hpText->setVisible(true);
  this->_ressText->setVisible(true);
  this->_ressourcesCarryText->setVisible(true);
  this->_description->setVisible(true);
  this->_building->setVisible(true);
}

void	GUIG::Annotation::update(const Game::AElement *element) {
  const Game::RessourcesSpot *r = dynamic_cast<const Game::RessourcesSpot*>(element);
  if (r) {
    hideAll();
    int amount = 0;
    switch (r->getSpotType()) {
    case (Game::Ressources::GOLD):
      this->setName("Gold");
      break;
    case (Game::Ressources::WOOD):
      this->setName("Wood");
      break;
    }
    amount = r->getAmount();
    this->_armorText->setText("Amount: " + StringOfInt(amount));
    this->_armorText->setVisible(true);
    this->_nameText->setVisible(true);
    draw();
    return ;
  }
  showAll();
  this->setName(element->getInfos().data->name);
  this->setSpeed(element->getInfos().data->speed);
  this->setRange(element->getInfos().data->attackRange);
  this->setAttack(element->getInfos().data->attack);
  this->setArmor(element->getInfos().data->defense);
  this->setRessType(element->getInfos().data->typeRessources);
  this->setHPMax(element->getInfos().data->maxHP);
  this->setHP(element->getCurrentLife());
  this->setHPMaxBonus(element->getMaxLife() - element->getInfos().data->maxHP);
  this->setRangeBonus(element->getAttackRange() - element->getInfos().data->attackRange);
  this->setAttackBonus(element->getAttack() - element->getInfos().data->attack);
  this->setArmor(element->getDefense() - element->getInfos().data->defense);
  this->setRess(element->getCurrentRessources());
  std::string description = element->getInfos().data->description;
  if (description.length() > 25) {
    description = description.substr(23) + "...";
  }
  this->_description->setText(description);

  const Game::Unit *unit = dynamic_cast<const Game::Unit*>(element);
  if (unit) {
    const Game::Ressources &ressources = unit->getRessources();
    int		gold, wood;
    gold = ressources.get(Game::Ressources::GOLD);
    wood = ressources.get(Game::Ressources::WOOD);
    this->_ressourcesCarryText->setVisible(false);
    if (gold > 0) {
      this->_ressourcesCarryText->setColor(Ogre::ColourValue(1, 1, 0));
      this->_ressourcesCarryText->setText("Gold: " + StringOfInt(gold));
      this->_ressourcesCarryText->setVisible(true);
    }
    else if (wood > 0) {
      this->_ressourcesCarryText->setColor(Ogre::ColourValue(0, 1, 0));
      this->_ressourcesCarryText->setText("Wood: " + StringOfInt(wood));
      this->_ressourcesCarryText->setVisible(true);
    }
  }
  this->_building->setVisible(false);
  if (element->getType() == Game::BUILDING) {
    const Game::Building *building = dynamic_cast<const Game::Building*>(element);
    if (building) {
      if (building->isBuilt() == false) {
	this->_building->setVisible(true);
      }
    }
  }
}
