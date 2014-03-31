//
// convert.hpp for PFA in /home/yannick/Documents/pfa/graphicClient/includes
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sun Feb 16 12:35:54 2014 Yannick Briffa
// Last update Sun Feb 16 12:40:26 2014 Yannick Briffa
//

#ifndef	__CONVERT_HPP__
# define __CONVERT_HPP__

# include	<sstream>

template<typename T>
T	toValue(std::string const &value)
{
  T	result;

  std::istringstream(value) >> result;
  return result;
}

template<typename T>
std::string	toString(T value)
{
  std::ostringstream	oss;

  oss << value;
  return (oss.str());
}

#endif
