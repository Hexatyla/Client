//
// RaceClient.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Mar 10 16:17:21 2014 geoffrey bauduin
// Last update Mon Mar 31 12:36:47 2014 geoffrey bauduin
//

#include	"Parser/Race.hpp"
#include	"Kernel/Manager.hpp"
#include	"Logger.hpp"
#include	"Factory/Kernel.hpp"
#include	"Kernel/Config.hpp"

#define RESSTYPE(x)	(static_cast<Kernel::ElementRessources::Type>(x))
#define TOCANAL(x)	(static_cast<Kernel::Time::Canalisation>(x))

Parser::Race::Race(void):
  Parser::ARace(),
  _tokensClient(), _categoriesFunc(), _allData() {
  // this->_tokensClient[VOICE] = "voice";
  // this->_tokensClient[VOICE_DIE] = "voice_die";
  // this->_tokensClient[VOICE_BIRTH] = "voice_birth";
  // this->_tokensClient[VOICE_ATTACK] = "voice_attack";
  this->_tokensClient[ICON] = "icon";
  this->_tokensClient[MODEL] = "model";

  for (auto it : this->_tokensClient) {
    this->_dataFields.push_back(it.second);
  }
  this->_dataFields.push_back(this->_tokens[DESCRIPTION]);

  this->_categoriesFunc[this->_categories[RACES]] = &Parser::Race::parseRace;
  this->_categoriesFunc[this->_categories[ELEMENTS]] = &Parser::Race::parseElements;

  this->_parseOrder.push_back(this->_categories[RACES]);
  this->_parseOrder.push_back(this->_categories[ELEMENTS]);

  this->_verbose = true;
}

Parser::Race::~Race(void) {

}

void	Parser::Race::createData(const Kernel::Serial &serial, const Json::Value &item, ::Game::Type type) {
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
						     1.0,
						     item[this->_tokens[PASSTHROUGH]].asInt(),
						     RESSTYPE(item[this->_tokens[TYPERESSOURCE]].asInt()),
						     item[this->_tokens[RESSOURCE]].asInt(),
						     item[this->_tokens[REGENRESSOURCE]].asInt(),
						     item[this->_tokens[SIGHT_D]].asDouble(),
						     item[this->_tokens[SIGHT_N]].asDouble()
						     );
  // data->voice = item[this->_tokensClient[VOICE]].asString();
  // data->voiceBirth = item[this->_tokensClient[VOICE_BIRTH]].asString();
  // data->voiceDie = item[this->_tokensClient[VOICE_DIE]].asString();
  // data->voiceAttack = item[this->_tokensClient[VOICE_ATTACK]].asString();
  data->voice = "";
  data->voiceBirth = "";
  data->voiceDie = "";
  data->voiceAttack = "";
  data->icon = item[this->_tokensClient[ICON]].asString();
  data->model = item[this->_tokensClient[MODEL]].asString();
  data->description = item[this->_tokens[DESCRIPTION]].asString();
  this->_kData[serial] = data;
  this->_allData.push_back(serial);
}

bool	Parser::Race::_parse(const std::string &category, const Json::Value &data) {
  return (this->_categoriesFunc[category] && (this->*_categoriesFunc[category])(data));
}

void	Parser::Race::emptyContainer(bool rm) {
  Parser::ARace::emptyContainer(rm);
  this->_allData.assign(0, "");
}

const Parser::ARace::Container	Parser::Race::parse(const std::string &filename, std::vector<Kernel::Serial> &data) {
  const Parser::ARace::Container c = Parser::ARace::parse(filename);
  data = this->_allData;
  data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::GOLD_SPOT_SERIAL));
  data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::WOOD_SPOT_SERIAL));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::CARRY_RESSOURCES_CAPACITY));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::HARVEST_CAPACITY));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_GOLD_CAPACITY));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_WOOD_CAPACITY));
  // data.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::PATROL_CAPACITY));
  return (c);
}
