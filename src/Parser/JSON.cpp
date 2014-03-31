//
// JSONParser.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 11:04:34 2014 geoffrey bauduin
// Last update Wed Mar 12 11:46:42 2014 geoffrey bauduin
//

#include	"Utils/FileReader.hpp"
#include	"Parser/JSON.hpp"
#include	"Logger.hpp"

Parser::JSON::JSON(void) {}

Parser::JSON::~JSON(void) {}

bool	Parser::JSON::parse(const std::string &file, Json::Value &root) {
  FileReader fReader;
  Json::Reader reader;
  bool success = false;
  try {
    fReader.read(file);
    success = reader.parse(fReader.getContent(), root);
    if (!success) {
      Logger::getInstance()->addDecalage();
      Logger::getInstance()->log("Bad JSON format.", Logger::FATAL);
      Logger::getInstance()->removeDecalage();
    }
  }
  catch (FileReader::Exception *e) {
    delete e;
    Logger::getInstance()->addDecalage();
    Logger::getInstance()->log("Failed to open file.", Logger::FATAL);
    Logger::getInstance()->removeDecalage();
    success = false;
  }
  return (success);
}
