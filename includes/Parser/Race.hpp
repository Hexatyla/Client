//
// RaceClient.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Mar 10 16:14:10 2014 geoffrey bauduin
// Last update Thu Mar 13 16:27:27 2014 geoffrey bauduin
//

#ifndef PARSER_RACECLIENT_HPP_
# define PARSER_RACECLIENT_HPP_

#include	"Parser/ARace.hpp"

namespace	Parser {

  class	Race: public Parser::ARace {

  protected:
    enum TokenClient { VOICE, VOICE_DIE, VOICE_BIRTH, VOICE_ATTACK, ICON, MODEL };

    std::map<TokenClient, std::string>	_tokensClient;
    std::map<std::string, bool (Parser::Race::*)(const Json::Value &)> _categoriesFunc;
    std::vector<Kernel::Serial>		_allData;

  protected:
    virtual void	createData(const Kernel::Serial &, const Json::Value &, ::Game::Type);

    virtual bool	_parse(const std::string &, const Json::Value &);

    virtual void	emptyContainer(bool);

  public:
    Race(void);
    virtual ~Race(void);

    const Container	parse(const std::string &, std::vector<Kernel::Serial> &);

  };

}

#endif
