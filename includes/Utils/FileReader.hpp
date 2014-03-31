//
// FileReader.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 11:14:21 2014 geoffrey bauduin
// Last update Tue Jan 21 11:43:09 2014 geoffrey bauduin
//

#ifndef FILEREADER_HPP_
# define FILEREADER_HPP_

#include	<stdexcept>

class	FileReader {

public:
  class	Exception: public std::exception {

  private:
    std::string	_what;

  public:
    Exception(const std::string &) throw();
    virtual ~Exception(void) throw();

    const char *what(void) const throw();

  };

private:
  std::string	_content;

public:
  FileReader(void);
  ~FileReader(void);

  void	read(const std::string &);
  const std::string &getContent(void) const;

};

#endif
