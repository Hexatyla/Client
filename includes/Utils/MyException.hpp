//
// MyException.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Oct 15 21:32:48 2013 geoffrey bauduin
// Last update Tue Oct 15 21:38:50 2013 geoffrey bauduin
//

#ifndef MY_EXCEPTION_HPP_
# define MY_EXCEPTION_HPP_

#include	<string>
#include	<exception>

class	MyException: public std::exception {

private:
  std::string	_what;

public:
  MyException(const std::string &) throw();
  virtual ~MyException(void) throw() {}

  virtual const char	*what(void) const throw();

};

#endif
