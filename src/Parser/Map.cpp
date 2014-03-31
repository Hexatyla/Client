//
// Map.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Feb 14 22:54:29 2014 geoffrey bauduin
// Last update Tue Mar 11 15:58:01 2014 geoffrey bauduin
//

#include	<cstddef>
#include	"Parser/Map.hpp"
#include	"Logger.hpp"
#ifdef __SERVER__
# include	"Factory/Server.hpp"
#else
# include	"Factory/Game.hpp"
#endif

Parser::Map::Map(void):
  _tokens(), _tokensRessource(), _hashtabRessourcesType(),
  _tokensStart() {
  this->_tokens[X] = "x";
  this->_tokens[Y] = "y";
  this->_tokens[Z] = "z";
  this->_tokens[RESSOURCE] = "ressource";

  this->_tokensRessource[TYPE] = "typex";
  this->_tokensRessource[XR] = "x";
  this->_tokensRessource[YR] = "y";
  this->_tokensRessource[VALUE] = "value";

  this->_hashtabRessourcesType["wood"] = Game::Ressources::WOOD;
  this->_hashtabRessourcesType["gold"] = Game::Ressources::GOLD;

  this->_tokensStart[ST_X] = "x";
  this->_tokensStart[ST_Y] = "y";

}

Parser::Map::~Map(void) {

}

bool	Parser::Map::check(const Json::Value &root) {
  if (root.isMember("Map") == false) {
    Logger::getInstance()->log("Cannot find >Map< in file", Logger::FATAL);
    return (false);
  }
  const Json::Value &map = root["Map"];
  for (auto it : this->_tokens) {
    if (map.isMember(it.second) == false) {
      Logger::getInstance()->logf("Cannot find >%s< in file", Logger::FATAL, &it.second);
      return (false);
    }
  }
#ifdef __SERVER__
  const Json::Value &ressources = map[this->_tokens[RESSOURCE]];
  for (unsigned int i = 0 ; i < ressources.size() ; ++i) {
    for (auto it : this->_tokensRessource) {
      if (ressources[i].isMember(it.second) == false) {
	Logger::getInstance()->logf("Cannot find >%s< in file", Logger::FATAL, &it.second);
	return (false);
      }
    }
  }
  if (!root.isMember("Start")) {
    Logger::getInstance()->log("Cannot find >Start< in file", Logger::FATAL);
    return (false);
  }
  for (unsigned int i = 0 ; i < root["Start"].size() ; ++i) {
    for (auto it : this->_tokensStart) {
      if (root["Start"][i].isMember(it.second) == false) {
	Logger::getInstance()->logf("Cannot find >%s< in file", Logger::FATAL, &it.second);
      }
    }
  }
#endif
  return (true);
}

bool	Parser::Map::parseMap(const Json::Value &map, std::vector<unsigned int> &z, unsigned int &x,
			      unsigned int &y) {
  x = map[this->_tokens[X]].asInt();
  y = map[this->_tokens[Y]].asInt();
  const Json::Value &zz = map[this->_tokens[Z]];
  for (unsigned int i = 0 ; i < zz.size() ; ++i) {
    z.push_back(zz[i].asInt());
  }
  if (z.size() != x * y) {
    Logger::getInstance()->log("Map does not have the correct number of Z values.", Logger::FATAL);
    return (false);
  }
  return (true);
}

#ifdef __SERVER__

bool	Parser::Map::parseSpots(const Json::Value &ressources, std::vector<Server::Map::Spot> &spots) {
  for (unsigned int j = 0 ; j < ressources.size() ; ++j) {
    Server::Map::Spot spot;
    spot.type = this->_hashtabRessourcesType[ressources[j][this->_tokensRessource[TYPE]].asString()];
    spot.x = ressources[j][this->_tokensRessource[XR]].asDouble();
    spot.y = ressources[j][this->_tokensRessource[YR]].asDouble();
    spot.amount = ressources[j][this->_tokensRessource[VALUE]].asInt();
    spots.push_back(spot);
  }
  return (true);
}

bool	Parser::Map::parseStart(const Json::Value &start, std::vector<std::pair<double, double> > &starter) {
  for (unsigned int j = 0 ; j < start.size() ; ++j) {
    starter.push_back(std::make_pair(start[j][this->_tokensStart[ST_X]].asDouble(),
				     start[j][this->_tokensStart[ST_Y]].asDouble()));
  }
  return (true);
}

#endif

Game::Map	*Parser::Map::parse(const std::string &filename) {
  Logger::getInstance()->logf("Starting to parse %s", Logger::INFORMATION, &filename);
  Game::Map *_map = NULL;
  Json::Value root;
  if (!Parser::JSON::getInstance()->parse(filename, root)) {
    Logger::getInstance()->logf("Cannot parse %s", Logger::FATAL, &filename);
    return (NULL);
  }
  Logger::getInstance()->addDecalage();
  Logger::getInstance()->log("Parsing ...", Logger::INFORMATION);
  if (this->check(root) == false) {
    Logger::getInstance()->removeDecalage();
    return (NULL);
  }
  const Json::Value &map = root["Map"];

  std::vector<unsigned int> z;
  unsigned int x, y;
  if (!this->parseMap(map, z, x, y)) {
    Logger::getInstance()->removeDecalage();
    return (NULL);
  }

#ifdef __SERVER__
  const Json::Value &ressources = map[this->_tokens[RESSOURCE]];
  std::vector<Server::Map::Spot> spots;
  std::vector<std::pair<double, double> > starter;
  if (this->parseSpots(ressources, spots) == false) {
    Logger::getInstance()->removeDecalage();
    return (NULL);
  }
  const Json::Value &start = root["Start"];
  if (this->parseStart(start, starter) == false) {
    Logger::getInstance()->removeDecalage();
    return (NULL);
  }
  _map = Factory::Server::Map::create(x, y, z, spots, starter);
#else
  _map = Factory::Game::Map::create(x, y, z);
#endif

  Logger::getInstance()->removeDecalage();
  Logger::getInstance()->log("Parsing de la map OK", Logger::INFORMATION);
  return (_map);
}
