//
// ARace.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Mar 10 15:55:11 2014 geoffrey bauduin
// Last update Tue Mar 25 18:37:40 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Parser/ARace.hpp"
#include	"Factory/Game.hpp"
#include	"Logger.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Kernel/Manager.hpp"
#include	"Factory/Kernel.hpp"
#include	"Kernel/Config.hpp"

#define RESSTYPE(x)	(static_cast<Kernel::ElementRessources::Type>(x))
#define TOCANAL(x)	(static_cast<Kernel::Time::Canalisation>(x))

Parser::ARace::ARace(void):
  _mutex(new Mutex), _verbose(true),
  _tokens(), _categories(), _reqCategories(), _dataFields(), _costFields(),
  _timerFields(), _effectsFields(), _capacityFields(),
  _tokensTypes(), _parseOrder(), _linkedElements(), _linkedElementsList(),
  _requirementsList(), _tokenLEList(),  _defaultCapacities(),
  _effectTypeHashtab(), _effectSideHashtab(), _gameTypeHashtab(), _capacityTargetHashtab(),
  _leListToType(),
  _ptrFunc(),
  _parsedUnits(), _parsedBuildings(), _parsedHeroes(), _parsedObjects(), _parsedProjectiles(),
  _parsedCapacities(), _parsedEffects(), _parsedAmeliorations(),
  _linkedElementsData(), _requirementsData(),
  _resolveData(), _resolveRequirements(),
  _kData(), _kCost(), _kTimer(), _kBData(), _kCData(), _kEffect(),
  _itemReq() {

  this->_tokens[TYPE] = "type";
  this->_tokens[NAME] = "name";
  this->_tokens[DESCRIPTION] = "description";
  this->_tokens[HITBOX] = "hitbox";
  this->_tokens[PASSTHROUGH] = "passThrought";
  this->_tokens[ATTACK] = "attack";
  this->_tokens[DEFENSE] = "defense";
  this->_tokens[HP] = "hp";
  this->_tokens[REGENHP] = "regenHp";
  this->_tokens[TYPERESSOURCE] = "typeRessource";
  this->_tokens[RESSOURCE] = "Ressource";
  this->_tokens[REGENRESSOURCE] = "regenRessource";
  this->_tokens[ATTACKSPEED] = "attackSpeed";
  this->_tokens[CRITICALSTRIKE] = "critick";
  this->_tokens[SPEED] = "speed";
  this->_tokens[SIGHT_N] = "vision_night";
  this->_tokens[SIGHT_D] = "vision_day";
  this->_tokens[COST_R1] = "cost_gold";
  this->_tokens[COST_R2] = "cost_wood";
  this->_tokens[COST_R3] = "cost_food";
  this->_tokens[COST_TYPE_RESS] = "cost_type_ress";
  this->_tokens[COST_RESS] = "cost_ress";
  this->_tokens[COST_LIFE] = "cost_life";
  this->_tokens[CAN_AUTO] = "can_auto";
  this->_tokens[IS_AUTO] = "is_auto";
  this->_tokens[CANALISATION] = "canalisation";
  this->_tokens[CANALISATION_WHEN] = "canalisation_when";
  this->_tokens[COOLDOWN] = "cooldown";
  this->_tokens[CREATION] = "creation";
  this->_tokens[DURATION] = "duration";
  this->_tokens[ELEM_TYPE_RESS] = "elem_type_ress";
  this->_tokens[ELEM_LIFE_ACT] = "elem_life_act";
  this->_tokens[ELEM_RESS] = "elem_ress";
  this->_tokens[RACE] = "race";
  this->_tokens[RANGE] = "range";
  this->_tokens[LINK_ELEMENTS] = "elements";
  this->_tokens[REQUIREMENTS] = "requirements";
  this->_tokens[EFFECT_TYPE] = "effect_type";
  this->_tokens[EFFECT_EQUIP] = "effect_equip";
  this->_tokens[EFFECT_CIBLE] = "effect_cible";
  this->_tokens[EFFECT_LINK] = "effect_link";
  this->_tokens[CAPACITY_TARGET] = "cible";

  this->_categories[RACES] = "Races";
  this->_categories[ELEMENTS] = "Elements";

  this->_reqCategories.push_back(this->_categories[RACES]);
  this->_reqCategories.push_back(this->_categories[ELEMENTS]);

  this->_dataFields.push_back(this->_tokens[RACE]);
  this->_dataFields.push_back(this->_tokens[NAME]);
  this->_dataFields.push_back(this->_tokens[ATTACK]);
  this->_dataFields.push_back(this->_tokens[DEFENSE]);
  this->_dataFields.push_back(this->_tokens[REGENHP]);
  this->_dataFields.push_back(this->_tokens[SPEED]);
  this->_dataFields.push_back(this->_tokens[CRITICALSTRIKE]);
  this->_dataFields.push_back(this->_tokens[HP]);
  this->_dataFields.push_back(this->_tokens[HITBOX]);
  this->_dataFields.push_back(this->_tokens[PASSTHROUGH]);
  this->_dataFields.push_back(this->_tokens[TYPERESSOURCE]);
  this->_dataFields.push_back(this->_tokens[RESSOURCE]);
  this->_dataFields.push_back(this->_tokens[REGENRESSOURCE]);
  this->_dataFields.push_back(this->_tokens[SIGHT_D]);
  this->_dataFields.push_back(this->_tokens[SIGHT_N]);
  this->_dataFields.push_back(this->_tokens[RANGE]);

  this->_costFields.push_back(this->_tokens[COST_R1]);
  this->_costFields.push_back(this->_tokens[COST_R2]);
  this->_costFields.push_back(this->_tokens[COST_R3]);
  this->_costFields.push_back(this->_tokens[COST_TYPE_RESS]);
  this->_costFields.push_back(this->_tokens[COST_RESS]);
  this->_costFields.push_back(this->_tokens[COST_LIFE]);

  this->_timerFields.push_back(this->_tokens[CANALISATION]);
  this->_timerFields.push_back(this->_tokens[CREATION]);
  this->_timerFields.push_back(this->_tokens[DURATION]);
  this->_timerFields.push_back(this->_tokens[COOLDOWN]);

  this->_effectsFields.push_back(this->_tokens[EFFECT_TYPE]);
  this->_effectsFields.push_back(this->_tokens[EFFECT_EQUIP]);
  this->_effectsFields.push_back(this->_tokens[EFFECT_CIBLE]);
  this->_effectsFields.push_back(this->_tokens[EFFECT_LINK]);

  this->_capacityFields.push_back(this->_tokens[CAN_AUTO]);
  this->_capacityFields.push_back(this->_tokens[IS_AUTO]);
  this->_capacityFields.push_back(this->_tokens[CAPACITY_TARGET]);

  this->_linkedElements.push_back(this->_tokens[LINK_ELEMENTS]);
  this->_linkedElements.push_back(this->_tokens[REQUIREMENTS]);

  this->_tokenLEList[LE_UNITS] = "Units";
  this->_tokenLEList[LE_BUILDINGS] = "Buildings";
  this->_tokenLEList[LE_HEROS] = "Heros";
  this->_tokenLEList[LE_OBJECTS] = "Objects";
  this->_tokenLEList[LE_PROJECTILES] = "Projectiles";
  this->_tokenLEList[LE_AMELIORATIONS] = "Ameliorations";
  this->_tokenLEList[LE_SPELLS] = "Spells";
  this->_tokenLEList[LE_CAPACITY] = "Capacity";
  this->_tokenLEList[LE_EFFECT] = "Effects";

  this->_leListToType[LE_UNITS] = ::Game::UNIT;
  this->_leListToType[LE_BUILDINGS] = ::Game::BUILDING;
  this->_leListToType[LE_HEROS] = ::Game::HERO;
  this->_leListToType[LE_OBJECTS] = ::Game::OBJECT;
  this->_leListToType[LE_PROJECTILES] = ::Game::PROJECTILE;
  this->_leListToType[LE_AMELIORATIONS] = ::Game::AMELIORATION;
  this->_leListToType[LE_CAPACITY] = ::Game::CAPACITY;
  this->_leListToType[LE_EFFECT] = ::Game::EFFECT;

  this->_linkedElementsList.push_back(this->_tokenLEList[LE_UNITS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_BUILDINGS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_HEROS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_OBJECTS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_PROJECTILES]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_AMELIORATIONS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_SPELLS]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_CAPACITY]);
  this->_linkedElementsList.push_back(this->_tokenLEList[LE_EFFECT]);

  // this->_requirementsList.push_back(this->_tokenLEList[LE_UNITS]);
  this->_requirementsList.push_back(this->_tokenLEList[LE_BUILDINGS]);
  // this->_requirementsList.push_back(this->_tokenLEList[LE_HEROS]);
  this->_requirementsList.push_back(this->_tokenLEList[LE_OBJECTS]);
  // this->_requirementsList.push_back(this->_tokenLEList[LE_PROJECTILES]);
  this->_requirementsList.push_back(this->_tokenLEList[LE_AMELIORATIONS]);
  // this->_requirementsList.push_back(this->_tokenLEList[LE_SPELLS]);
  // this->_requirementsList.push_back(this->_tokenLEList[LE_CAPACITY]);

  this->_tokensTypes[UNIT] = "Unit";
  this->_tokensTypes[BUILDING] = "Building";
  this->_tokensTypes[HERO] = "Heros";
  this->_tokensTypes[OBJECT] = "Object";
  this->_tokensTypes[PROJECTILE] = "Projectile";
  this->_tokensTypes[CAPACITY] = "Capacity";
  this->_tokensTypes[EFFECT] = "Effect";
  this->_tokensTypes[AMELIORATION] = "Amelioration";
  this->_tokensTypes[SPELL] = "Spells";

  this->_effectTypeHashtab["none"] = Kernel::Effect::NONE;
  this->_effectTypeHashtab["invoke"] = Kernel::Effect::INVOCATION;
  this->_effectTypeHashtab["stun"] = Kernel::Effect::STUN;
  this->_effectTypeHashtab["aura"] = Kernel::Effect::AURA;
  this->_effectTypeHashtab["teleporting"] = Kernel::Effect::TELEPORTING;

  this->_effectSideHashtab["all"] = Kernel::Effect::ALL;
  this->_effectSideHashtab["enemy"] = Kernel::Effect::ENEMY;
  this->_effectSideHashtab["ally"] = Kernel::Effect::ALLY;

  this->_gameTypeHashtab["object"] = Game::OBJECT;
  this->_gameTypeHashtab["building"] = Game::BUILDING;
  this->_gameTypeHashtab["hero"] = Game::HERO;
  this->_gameTypeHashtab["projectile"] = Game::PROJECTILE;
  this->_gameTypeHashtab["unit"] = Game::UNIT;
  this->_gameTypeHashtab["all"] = Game::ALL_T;

  this->_capacityTargetHashtab["item"] = Game::Capacity::ITEM;
  this->_capacityTargetHashtab["zone"] = Game::Capacity::ZONE;
  this->_capacityTargetHashtab["self"] = Game::Capacity::NONE;

  this->_ptrFunc[this->_tokensTypes[UNIT]] = &Parser::ARace::parseUnit;
  this->_ptrFunc[this->_tokensTypes[BUILDING]] = &Parser::ARace::parseBuilding;
  this->_ptrFunc[this->_tokensTypes[HERO]] = &Parser::ARace::parseHero;
  this->_ptrFunc[this->_tokensTypes[OBJECT]] = &Parser::ARace::parseObject;
  this->_ptrFunc[this->_tokensTypes[PROJECTILE]] = &Parser::ARace::parseProjectile;
  this->_ptrFunc[this->_tokensTypes[CAPACITY]] = &Parser::ARace::parseCapacity;
  this->_ptrFunc[this->_tokensTypes[EFFECT]] = &Parser::ARace::parseEffect;
  this->_ptrFunc[this->_tokensTypes[AMELIORATION]] = &Parser::ARace::parseAmelioration;

  this->_resolveData[Game::UNIT].push_back(LE_CAPACITY);
  this->_resolveData[Game::UNIT].push_back(LE_AMELIORATIONS);

  this->_resolveData[Game::BUILDING].push_back(LE_UNITS);
  this->_resolveData[Game::BUILDING].push_back(LE_CAPACITY);
  this->_resolveData[Game::BUILDING].push_back(LE_AMELIORATIONS);
  this->_resolveData[Game::BUILDING].push_back(LE_HEROS);

  this->_resolveData[Game::HERO].push_back(LE_SPELLS);
  this->_resolveData[Game::HERO].push_back(LE_CAPACITY);
  this->_resolveData[Game::HERO].push_back(LE_AMELIORATIONS);

  this->_resolveData[Game::PROJECTILE].push_back(LE_EFFECT);

  this->_resolveData[Game::CAPACITY].push_back(LE_EFFECT);
  this->_resolveData[Game::CAPACITY].push_back(LE_PROJECTILES);

  this->_resolveData[Game::EFFECT].push_back(LE_EFFECT);

  this->_resolveRequirements.push_back(LE_BUILDINGS);
  this->_resolveRequirements.push_back(LE_AMELIORATIONS);

  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY));
  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::CARRY_RESSOURCES_CAPACITY));
  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::HARVEST_CAPACITY));
  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_GOLD_CAPACITY));
  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_WOOD_CAPACITY));
  this->_defaultCapacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::PATROL_CAPACITY));

}

Parser::ARace::~ARace(void) {
  delete this->_mutex;
}

const Kernel::Serial	Parser::ARace::getSerial(const Json::Value &item) {
  std::stringstream s;
  s << item;
  return (Kernel::create_serial(s.str()));
}

bool	Parser::ARace::check(const Json::Value &item, const std::vector<std::string> &fields,
			     const std::string &category) {
  for (auto it : fields) {
    if (!item.isMember(it)) {
      Logger::getInstance()->logf("Cannot find token >%s< in >%s<.", Logger::FATAL, &it, &category);
      return (false);
    }
  }
  return (true);
}


bool	Parser::ARace::checkCategories(const Json::Value &root) {
  for (auto it : this->_reqCategories) {
    if (root.isMember(it) == false) {
      Logger::getInstance()->logf("Cannot find category >%s< in race file.", Logger::FATAL, &it);
      return (false);
    }
  }
  return (true);
}

void	Parser::ARace::emptyContainer(bool rm) {
  if (rm) {
    for (auto it : this->_container) {
      if (it.second) {
	this->deleteRace(it.second);
      }
    }
  }
  this->_container.clear();
  this->_parsedUnits.clear();
  this->_parsedBuildings.clear();
  this->_parsedHeroes.clear();
  this->_parsedObjects.clear();
  this->_parsedProjectiles.clear();
  this->_parsedCapacities.clear();
  this->_parsedEffects.clear();
  this->_parsedAmeliorations.clear();
  this->_linkedElementsData.clear();
  this->_requirementsData.clear();
  if (rm) {
    for (auto it : this->_kData) {
      if (it.second) {
	Factory::Kernel::Data::remove(it.second);
      }
    }
    for (auto it : this->_kCost) {
      if (it.second) {
	Factory::Kernel::Cost::remove(it.second);
      }
    }
    for (auto it : this->_kTimer) {
      if (it.second) {
	Factory::Kernel::Time::remove(it.second);
      }
    }
    for (auto it : this->_kBData) {
      if (it.second) {
	Factory::Kernel::BuildingData::remove(it.second);
      }
    }
    for (auto it : this->_kCData) {
      if (it.second) {
	Factory::Kernel::CapacityData::remove(it.second);
      }
    }
    for (auto it : this->_kEffect) {
      if (it.second) {
	Factory::Kernel::Effect::remove(it.second);
      }
    }
    for (auto it : this->_itemReq) {
      if (it.second) {
	Factory::Game::Requirements::remove(it.second);
      }
    }
  }
  this->_kData.clear();
  this->_kCost.clear();
  this->_kTimer.clear();
  this->_kBData.clear();
  this->_kCData.clear();
  this->_kEffect.clear();
  this->_itemReq.clear();
}

bool	Parser::ARace::parseUnit(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE)) {
    return (false);
  }
  if (!this->_container[item["race"].asString()]) {
    std::string r = item["race"].asString();
    Logger::getInstance()->logf("Bad race name >%s<", Logger::FATAL, &r);
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Unit [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::UNIT);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_container[item[this->_tokens[RACE]].asString()]->addUnit(serial, NULL);
  this->_parsedUnits[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseBuilding(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_RACE | C_COST | C_TIMER | C_LE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Building [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::BUILDING);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_container[item[this->_tokens[RACE]].asString()]->addBuilding(serial, NULL);
  this->_parsedBuildings[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseHero(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE | C_RACE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Hero [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::HERO);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_container[item[this->_tokens[RACE]].asString()]->addHero(serial, NULL);
  this->_parsedHeroes[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseObject(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Object [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::OBJECT);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_parsedObjects[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseProjectile(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Projectile [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::PROJECTILE);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_parsedProjectiles[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseEffect(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE | C_EFFE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Effect [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::EFFECT);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->createEffectData(serial, item);
  this->_parsedEffects[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseCapacity(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE | C_CAPA)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Capacity [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::CAPACITY);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->createCapacityData(serial, item);
  this->_parsedCapacities[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

bool	Parser::ARace::parseAmelioration(const Kernel::Serial &serial, const Json::Value &item) {
  if (!this->doChecks(item, C_DATA | C_COST | C_TIMER | C_LE | C_RACE)) {
    return (false);
  }
  if (this->_verbose) {
    Logger::getInstance()->logf("Parsing Amelioration [%s]", Logger::INFORMATION, &serial);
  }
  this->createData(serial, item, ::Game::AMELIORATION);
  this->createCost(serial, item);
  this->createTimer(serial, item);
  this->_container[item[this->_tokens[RACE]].asString()]->addAmelioration(serial, NULL);
  this->_parsedAmeliorations[item[this->_tokens[NAME]].asString()] = serial;
  return (true);
}

const Parser::ARace::Container	Parser::ARace::parse(const std::string &filename) {
  ScopeLock s(this->_mutex);
  this->emptyContainer(false);
  if (this->_verbose) {
    Logger::getInstance()->logf("Starting to parse %s", Logger::INFORMATION, &filename);
  }
  Json::Value root;
  if (!Parser::JSON::getInstance()->parse(filename, root)) {
    Logger::getInstance()->logf("Cannot parse %s", Logger::FATAL, &filename);
    return (this->_container);
  }
  Logger::getInstance()->addDecalage();
  if (this->checkCategories(root) == false) {
    Logger::getInstance()->logf("Bad race file (%s)", Logger::FATAL, &filename);
    Logger::getInstance()->removeDecalage();
    return (this->_container);
  }
  for (auto it : this->_parseOrder) {
    if (!this->_parse(it, root[it])) {
      Logger::getInstance()->removeDecalage();
      Logger::getInstance()->logf("Stopped parsing of %s", Logger::FATAL, &filename);
      this->emptyContainer(true);
      return (this->_container);
    }
  }
  if (this->resolve() == false) {
    Logger::getInstance()->removeDecalage();
    Logger::getInstance()->logf("Stopped parsing of %s", Logger::FATAL, &filename);
    this->emptyContainer(true);
    return (this->_container);
  }
  Logger::getInstance()->removeDecalage();
  this->end();
  for (auto it : this->_container) {
    if (it.second) {
      it.second->refreshSerial();
      Logger::getInstance()->logf("Race -%s- has been created [%s]", Logger::INFORMATION,
				  &it.first, &it.second->serial());
    }
  }
  return (this->_container);
}

void	Parser::ARace::end(void) {
  Kernel::Manager *manager = Kernel::Manager::getInstance();
  for (auto it : this->_kData) {
    manager->addData(it.first, it.second);
  }
  for (auto it : this->_kCost) {
    manager->addCost(it.first, it.second);
  }
  for (auto it : this->_kTimer) {
    manager->addTimer(it.first, it.second);
  }
  for (auto it : this->_kBData) {
    manager->addBuildingData(it.first, it.second);
  }
  for (auto it : this->_kCData) {
    manager->addCapacityData(it.first, it.second);
  }
  for (auto it : this->_kCList) {
    manager->addCapacityList(it.first, it.second);
  }
  for (auto it : this->_kEffect) {
    manager->addEffect(it.first, it.second);
  }
  for (auto it : this->_itemReq) {
    Game::Race *race = this->getRaceContainingItem(it.first, this->_kData[it.first]->type);
    if (race) {
      race->setRequirements(it.first, it.second);
    }
  }
}

bool	Parser::ARace::parseRace(const Json::Value &races) {
  for (unsigned int i = 0 ; i < races.size() ; ++i) {
    this->_container[races[i].asString()] = this->createRace(races[i].asString(), "");
  }
  return (true);
}

::Game::Race	*Parser::ARace::createRace(const std::string &name, const Kernel::Serial &serial) const {
  return (Factory::Game::Race::create(name, serial));
}

void	Parser::ARace::deleteRace(::Game::Race *race) const {
  Factory::Game::Race::remove(race);
}

bool	Parser::ARace::parseElements(const Json::Value &elements) {
  for (unsigned int i = 0 ; i < elements.size() ; ++i) {
    const Json::Value &item = elements[i];
    bool status = true;
    if (!item.isMember("type") || !this->_ptrFunc[item["type"].asString()]) {
      status = false;
    }
    else {
      Kernel::Serial serial = this->getSerial(item);
      if (!(this->*_ptrFunc[item["type"].asString()])(serial, item)) {
	status = false;
      }
      else {
	Logger::getInstance()->addDecalage();
	if (!(this->parseLinkedElements(serial, item[this->_tokens[LINK_ELEMENTS]]))) {
	  status = false;
	}
	else if (!(this->parseRequirements(serial, item[this->_tokens[REQUIREMENTS]]))) {
	  status = false;
	}
	Logger::getInstance()->removeDecalage();
      }
    }
    if (status == false) {
      std::string t = item.isMember("type") ? item["type"].asString() : "UNKNOWN";
      Logger::getInstance()->logf("There was a problem while parsing an item of type %s", Logger::FATAL, &t);
      return (false);
    }

  }
  return (true);
}

bool	Parser::ARace::parseLinkedElements(const Kernel::Serial &serial, const Json::Value &links) {
  this->_linkedElementsData[serial];
  for (auto it : this->_tokenLEList) {
    for (unsigned int j = 0 ; j < links[it.second].size() ; ++j) {
      std::string data = links[it.second][j].asString();
      this->_linkedElementsData[serial][it.first].push_back(data);
      if (this->_verbose) {
	Logger::getInstance()->logf("Added %s in %s links of %s", Logger::DEBUG, &data, &it.second, &serial);
      }
    }
  }
  return (true);
}

bool	Parser::ARace::parseRequirements(const Kernel::Serial &serial, const Json::Value &requirements) {
  this->_requirementsData[serial];
  for (auto it : this->_tokenLEList) {
    for (unsigned int j = 0 ; j < requirements[it.second].size() ; ++j) {
      std::string data = requirements[it.second][j].asString();
      this->_requirementsData[serial][it.first].push_back(data);
      if (this->_verbose) {
	Logger::getInstance()->logf("Added %s in %s requirements of %s", Logger::DEBUG, &data, &it.second, &serial);
      }
    }
  }
  return (true);
}

bool	Parser::ARace::doChecks(const Json::Value &data, int mask) {
  bool result = true;
  if (mask & C_DATA) {
    result &= this->check(data, this->_dataFields, "Elements");
  }
  if (mask & C_COST) {
    result &= this->check(data, this->_costFields, "Elements");
  }
  if (mask & C_TIMER) {
    result &= this->check(data, this->_timerFields, "Elements");
  }
  if (mask & C_LE) {
    bool r = this->check(data, this->_linkedElements, "Elements");
    result &= r;
    if (r) {
      result &= this->check(data[this->_tokens[LINK_ELEMENTS]], this->_linkedElementsList, "Elements/elements");
      result &= this->check(data[this->_tokens[REQUIREMENTS]], this->_requirementsList, "Elements/Requirements");
    }
  }
  if (mask & C_RACE) {
    if (!this->_container[data["race"].asString()]) {
      result &= false;
      std::string r = data["race"].asString();
      Logger::getInstance()->logf("Bad race name >%s<", Logger::FATAL, &r);
    }
  }
  if (mask & C_CAPA) {
    result &= this->check(data, this->_capacityFields, "Elements");
  }
  if (mask & C_EFFE) {
    result &= this->check(data, this->_effectsFields, "Elements");
  }
  return (result);
}

const Kernel::Serial	Parser::ARace::getSerial(::Game::Type type, const std::string &name) {
  switch (type) {
  case Game::UNIT:
    return (this->_parsedUnits[name]);
  case Game::BUILDING:
    return (this->_parsedBuildings[name]);
  case Game::HERO:
    return (this->_parsedHeroes[name]);
  case Game::OBJECT:
    return (this->_parsedObjects[name]);
  case Game::PROJECTILE:
    return (this->_parsedProjectiles[name]);
  case Game::CAPACITY:
    if (this->_parsedCapacities[name] == "") {
      std::vector<std::string>::iterator pos = std::find(this->_defaultCapacities.begin(), this->_defaultCapacities.end(), name);
      if (pos == this->_defaultCapacities.end()) {
	return ("");
      }
      return (*pos);
    }
    return (this->_parsedCapacities[name]);
  case Game::EFFECT:
    return (this->_parsedEffects[name]);
  case Game::AMELIORATION:
    return (this->_parsedAmeliorations[name]);
  default:
    return ("");
  }
}

bool	Parser::ARace::resolve(void) {
  return (this->linkElements() && this->linkRequirements());
}

bool	Parser::ARace::linkElements(void) {
  const Kernel::Data *data;
  for (auto leData : this->_linkedElementsData) {
    data = this->_kData[leData.first];
    if (data == NULL) {
      Logger::getInstance()->logf("Cannot find item with serial [%s]", Logger::FATAL, &leData.first);
      return (false);
    }
    const Game::Race *race = this->getRaceContainingItem(leData.first, data->type);
    for (auto type : this->_resolveData[data->type]) {
      for (auto name : leData.second[type]) {
	const Kernel::Serial serial = this->getSerial(this->_leListToType[type], name);
	if (serial == "") {
	  Logger::getInstance()->logf("Cannot find an item with name >%s<", Logger::FATAL, &name);
	  return (false);
	}
	if (this->canAddElementToElement(race, name, serial, this->_leListToType[type]) == false) {
	  Logger::getInstance()->logf("Cannot add element %s to element %s", Logger::FATAL, &name, &data->name);
	  return (false);
	}
      }
      this->addElementsToElement(leData.first, data->type, this->_leListToType[type], leData.second[type]);
    }
  }
  return (true);
}

bool	Parser::ARace::linkRequirements(void) {
  const Kernel::Data *data;
  for (auto leReq : this->_requirementsData) {
    data = this->_kData[leReq.first];
    if (data == NULL) {
      Logger::getInstance()->logf("Cannot find item with serial [%s]", Logger::FATAL, &leReq.first);
      return (false);
    }
    Game::Race *race = this->getRaceContainingItem(leReq.first, data->type);
    std::map<Game::Type, std::vector<Kernel::Serial> > d;
    for (auto type : this->_resolveRequirements) {
      for (auto name : leReq.second[type]) {
	const Kernel::Serial serial = this->getSerial(this->_leListToType[type], name);
	if (serial == "") {
	  Logger::getInstance()->logf("Cannot find an item with name >%s<", Logger::FATAL, &name);
	  return (false);
	}
	if (this->canAddElementToElement(race, name, serial, this->_leListToType[type]) == false) {
	  Logger::getInstance()->logf("Cannot push element %s into %s requirements", Logger::FATAL,
				      &name, &data->name);
	  return (false);
	}
	d[this->_leListToType[type]].push_back(serial);
      }
    }
    this->createRequirements(race, data->serial, d);
  }
  return (true);
}

void	Parser::ARace::createRequirements(Game::Race *, const Kernel::Serial &serial,
					  const std::map<Game::Type, std::vector<Kernel::Serial> > &data) {
  Game::Requirements *requirements = Factory::Game::Requirements::create();
  if (this->_verbose) {
    Logger::getInstance()->logf("Creating requirements for [%s]", Logger::INFORMATION, &serial);
  }
  for (auto it : data) {
    for (auto serial : it.second) {
      switch (it.first) {
      case Game::BUILDING:
	requirements->addBuilding(serial);
	break;
      case Game::AMELIORATION:
	requirements->addAmelioration(serial);
	break;
      default:
	break;
      }
    }
  }
  this->_itemReq[serial] = requirements;
}

Game::Race *Parser::ARace::getRaceContainingItem(const Kernel::Serial &serial, ::Game::Type type) {
  for (auto it : this->_container) {
    if (it.second && it.second->hasItem(serial, type)) {
      return (it.second);
    }
  }
  return (NULL);
}

bool	Parser::ARace::canAddElementToElement(const Game::Race *race, const std::string &name,
					      const Kernel::Serial &element, ::Game::Type type) const {
  if (race) {
    switch (type) {
    case Game::UNIT:
    case Game::HERO:
    case Game::BUILDING:
    case Game::AMELIORATION:
      if (!race->hasItem(element, type)) {
	Logger::getInstance()->log("Items are not in the same race.", Logger::FATAL);
	return (false);
      }
      break;
    case Game::CAPACITY:
      if (this->_parsedCapacities.find(name) == this->_parsedCapacities.end() &&
	  std::find(this->_defaultCapacities.begin(), this->_defaultCapacities.end(), name) == this->_defaultCapacities.end()) {
	Logger::getInstance()->logf("Unknown capacity : %s", Logger::FATAL, &name);
	return (false);
      }
      break;
    default:
      break;
    }
  }
  return (true);
}

void	Parser::ARace::addElementsToElement(const Kernel::Serial &serial, ::Game::Type sType,
					    ::Game::Type type, const std::vector<std::string> &items) {
  switch (type) {
  case Game::CAPACITY:
    this->createCapacityList(serial, items);
    break;
  case Game::HERO:
  case Game::UNIT:
    if (sType == Game::BUILDING) {
      this->createBuildingData(serial, items);
    }
    break;
  case Game::AMELIORATION:
    this->createAmeliorationData(serial, items);
    break;
  case Game::EFFECT:
    if (sType == Game::CAPACITY) {
      this->addCapacityEffects(serial, items);
    }
    else if (sType == Game::EFFECT) {
      this->addEffectEffects(serial, items);
    }
    break;
  case Game::PROJECTILE:
    if (sType == Game::CAPACITY) {
      this->addCapacityProjectiles(serial, items);
    }
    break;
  case Game::SPELLS:
    break;
  default:
    if (this->_verbose) {
      Logger::getInstance()->logf("Type >%d< not handled in Parser::ARace::addElementsToElement", Logger::FATAL, type);
    }
    break;
  }
}

void	Parser::ARace::createAmeliorationData(const Kernel::Serial &serial, const std::vector<std::string> &items) {
  if (this->_kData[serial] == NULL) {
    std::string s = __PRETTY_FUNCTION__;
    Logger::getInstance()->logf("%s", Logger::FATAL, &s);
    return ;
  }
  std::vector<Kernel::Serial> ameliorations;
  for (auto it : items) {
    const Kernel::Serial s = this->getSerial(Game::AMELIORATION, it);
    ameliorations.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Amelioration %s to Item [%s]", Logger::INFORMATION, &s, &serial);
    }
  }
  this->_kData[serial]->ameliorations = ameliorations;
}


void	Parser::ARace::createData(const Kernel::Serial &serial, const Json::Value &item, ::Game::Type type) {
  Kernel::Data *data = Factory::Kernel::Data::create(type,
						     item[this->_tokens[NAME]].asString(),
						     serial,
						     item[this->_tokens[ATTACK]].asInt(),
						     item[this->_tokens[DEFENSE]].asInt(),
						     item[this->_tokens[REGENHP]].asInt(),
						     item[this->_tokens[SPEED]].asInt(),
						     item[this->_tokens[CRITICALSTRIKE]].asDouble(),
						     item[this->_tokens[HP]].asInt(),
						     item[this->_tokens[HITBOX]].asDouble(),
						     item[this->_tokens[RANGE]].asDouble(),
						     item[this->_tokens[PASSTHROUGH]].asInt(),
						     RESSTYPE(item[this->_tokens[TYPERESSOURCE]].asInt()),
						     item[this->_tokens[RESSOURCE]].asInt(),
						     item[this->_tokens[REGENRESSOURCE]].asInt(),
						     item[this->_tokens[SIGHT_D]].asDouble(),
						     item[this->_tokens[SIGHT_N]].asDouble()
						     );
  this->_kData[serial] = data;
}

void	Parser::ARace::createCost(const Kernel::Serial &serial, const Json::Value &item) {
  Kernel::Cost *cost = Factory::Kernel::Cost::create(item[this->_tokens[COST_R1]].asInt(),
						     item[this->_tokens[COST_R2]].asInt(),
						     item[this->_tokens[COST_R3]].asInt(),
						     RESSTYPE(item[this->_tokens[COST_TYPE_RESS]].asInt()),
						     item[this->_tokens[COST_RESS]].asInt(),
						     item[this->_tokens[COST_LIFE]].asInt()
						     );
  this->_kCost[serial] = cost;
}

void	Parser::ARace::createTimer(const Kernel::Serial &serial, const Json::Value &item) {
  Kernel::Time::Canalisation when = item.isMember(this->_tokens[CANALISATION_WHEN]) ?
    TOCANAL(item[this->_tokens[CANALISATION_WHEN]].asInt()) : Kernel::Time::NONE;
  Kernel::Time *timer = Factory::Kernel::Time::create(item[this->_tokens[CANALISATION]].asDouble(),
						      item[this->_tokens[CREATION]].asDouble(),
						      item[this->_tokens[DURATION]].asDouble(),
						      item[this->_tokens[COOLDOWN]].asDouble(),
						      when
						      );
  this->_kTimer[serial] = timer;
}

void	Parser::ARace::createCapacityList(const Kernel::Serial &serial, const std::vector<std::string> &data) {
  Kernel::CapacityList *list = Factory::Kernel::CapacityList::create();
  for (auto it : data) {
    const Kernel::Serial s = this->getSerial(Game::CAPACITY, it);
    list->list.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Capacity %s [%s] to Object [%s]", Logger::INFORMATION, &it, &s, &serial);
    }
  }
  this->_kCList[serial] = list;
}

void	Parser::ARace::addEffectEffects(const Kernel::Serial &serial, const std::vector<std::string> &data) {
  if (this->_kEffect[serial] == NULL) {
    std::string s = __PRETTY_FUNCTION__;
    Logger::getInstance()->logf("%s", Logger::FATAL, &s);
    return ;
  }
  std::vector<Kernel::Serial> effects;
  for (auto it : data) {
    const Kernel::Serial s = this->getSerial(Game::EFFECT, it);
    effects.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Effect %s [%s] to Capacity [%s]", Logger::INFORMATION, &it, &s, &serial);
    }
  }
  this->_kEffect[serial]->effects = effects;
}

void	Parser::ARace::addCapacityEffects(const Kernel::Serial &serial, const std::vector<std::string> &data) {
  if (this->_kCData[serial] == NULL) {
    std::string s = __PRETTY_FUNCTION__;
    Logger::getInstance()->logf("%s", Logger::FATAL, &s);
    return ;
  }
  std::vector<Kernel::Serial> effects;
  for (auto it : data) {
    const Kernel::Serial s = this->getSerial(Game::EFFECT, it);
    effects.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Effect %s [%s] to Capacity [%s]", Logger::INFORMATION, &it, &s, &serial);
    }
  }
  this->_kCData[serial]->effects = effects;
}

void	Parser::ARace::addCapacityProjectiles(const Kernel::Serial &serial, const std::vector<std::string> &data) {
  if (this->_kCData[serial] == NULL) {
    std::string s = __PRETTY_FUNCTION__;
    Logger::getInstance()->logf("%s", Logger::FATAL, &s);
    return ;
  }
  std::vector<Kernel::Serial> projectiles;
  for (auto it : data) {
    const Kernel::Serial s = this->getSerial(Game::PROJECTILE, it);
    projectiles.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Projectile %s [%s] to Capacity [%s]", Logger::INFORMATION, &it, &s, &serial);
    }
  }
  this->_kCData[serial]->projectiles = projectiles;
}

void	Parser::ARace::createCapacityData(const Kernel::Serial &serial, const Json::Value &item) {
  Kernel::CapacityData *data = Factory::Kernel::CapacityData::create(item[this->_tokens[CAN_AUTO]].asBool(),
								     item[this->_tokens[IS_AUTO]].asBool());
  Game::Capacity::Target t = (this->_capacityTargetHashtab.find(item[this->_tokens[CAPACITY_TARGET]].asString()) != this->_capacityTargetHashtab.end() ? this->_capacityTargetHashtab[item[this->_tokens[CAPACITY_TARGET]].asString()] : Game::Capacity::NONE);
  data->target = t;
  this->_kCData[serial] = data;
}

void	Parser::ARace::createBuildingData(const Kernel::Serial &serial, const std::vector<std::string> &data) {
  Kernel::BuildingData *bData = (this->_kBData.find(serial) != this->_kBData.end() ? this->_kBData[serial] : Factory::Kernel::BuildingData::create());
  Kernel::Serial s;
  for (auto it : data) {
    s = this->getSerial(Game::UNIT, it);
    if (s == "") {
      s = this->getSerial(Game::HERO, it);
    }
    bData->units.push_back(s);
    if (this->_verbose) {
      Logger::getInstance()->logf("Adding Unit %s [%s] to Building [%s]", Logger::INFORMATION, &it, &s, &serial);
    }
  }
  this->_kBData[serial] = bData;
}

void	Parser::ARace::createEffectData(const Kernel::Serial &serial, const Json::Value &item) {
  Kernel::Effect::Type eType = (this->_effectTypeHashtab.find(item[this->_tokens[EFFECT_TYPE]].asString()) != this->_effectTypeHashtab.end() ?
				this->_effectTypeHashtab[item[this->_tokens[EFFECT_TYPE]].asString()] :
				Kernel::Effect::NONE);
  Kernel::Effect::TargetSide tSide = (this->_effectSideHashtab.find(item[this->_tokens[EFFECT_EQUIP]].asString()) != this->_effectSideHashtab.end() ?
				      this->_effectSideHashtab[item[this->_tokens[EFFECT_EQUIP]].asString()] :
				      Kernel::Effect::ALL);
  Game::Type gType = (this->_gameTypeHashtab.find(item[this->_tokens[EFFECT_CIBLE]].asString()) != this->_gameTypeHashtab.end() ?
		      this->_gameTypeHashtab[item[this->_tokens[EFFECT_CIBLE]].asString()] : Game::ALL_T);
  Kernel::Effect *effect = Factory::Kernel::Effect::create(eType, tSide, gType);
  this->_kEffect[serial] = effect;
}
