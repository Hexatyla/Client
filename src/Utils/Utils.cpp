//
// Utils.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Oct 21 13:29:31 2013 geoffrey bauduin
// Last update Mon Oct 21 13:30:25 2013 geoffrey bauduin
//

#include	<iostream>
#include	"Utils/Utils.hpp"

void	Utils::Utils::exception(const std::string &what) {
#ifdef __WINDOWS__
  // MessageBox
#else
  std::cerr << what << std::endl;
#endif
}

