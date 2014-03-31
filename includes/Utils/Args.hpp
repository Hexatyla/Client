//
// Args.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Oct 15 21:40:33 2013 geoffrey bauduin
// Last update Tue Oct 15 22:07:53 2013 geoffrey bauduin
//

#ifndef UTILS_ARGS_HPP_
# define UTILS_ARGS_HPP_

#include	<string>
#include	<map>

namespace	Utils {

  class	Args {

  private:
    std::map<char, int>	_trackM;
    std::map<char, int>	_track;
    int			_nbrArgs;
    char		**_args;

  public:
    Args(const std::string &, const std::string &);
    virtual ~Args(void) {}

    void	init(int, char **);
    bool	execute(void);
    int		get(char) const;

  };

}

#endif
