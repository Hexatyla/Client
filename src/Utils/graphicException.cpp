//
// graphicException.cpp for PFA in /home/yannick/Documents/pfa/graphicClient/src/utils
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Fri Jan 24 15:56:47 2014 Yannick Briffa
// Last update Mon Mar 31 12:44:24 2014 geoffrey bauduin
//

#include	"Utils/graphicException.hh"

graphicException::graphicException (std::string const &value) throw()
  : _what(value)
{
}

graphicException::~graphicException () throw()
{
}

const char *graphicException::what () const throw()
{
  return (_what.c_str());
}

