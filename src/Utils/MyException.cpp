//
// MyException.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Oct 15 21:32:47 2013 geoffrey bauduin
// Last update Tue Oct 15 21:38:23 2013 geoffrey bauduin
//

#include	"Utils/MyException.hpp"

MyException::MyException(const std::string &what) throw():
  _what(what) {

}

const char	*MyException::what(void) const throw() {
  return (this->_what.c_str());
}
