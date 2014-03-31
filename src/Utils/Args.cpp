//
// Args.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Oct 15 21:46:13 2013 geoffrey bauduin
// Last update Tue Oct 15 22:08:59 2013 geoffrey bauduin
//

#include	"Utils/MyException.hpp"
#include	"Utils/Args.hpp"

Utils::Args::Args(const std::string &mandatory, const std::string &nonMandatory):
  _trackM(), _track(), _nbrArgs(0), _args(NULL) {
  for (std::string::const_iterator it = mandatory.begin() ; it != mandatory.end() ; ++it) {
    this->_trackM[(*it)] = -1;
  }
  for (std::string::const_iterator it = nonMandatory.begin() ; it != nonMandatory.end() ; ++it) {
    this->_track[(*it)] = -1;
  }
}

void	Utils::Args::init(int argc, char **argv) {
  this->_nbrArgs = argc;
  this->_args = argv;
}

bool	Utils::Args::execute(void) {
  for (int i = 0 ; i < this->_nbrArgs ; ++i) {
    if (this->_args[i][0] == '-' && this->_args[i][1] && this->_args[i][2] == '\0') {
      if (this->_trackM.find(this->_args[i][1]) != this->_trackM.end()) {
	this->_trackM[this->_args[i][1]] = i;
      }
      else if (this->_track.find(this->_args[i][1]) != this->_track.end()) {
	this->_track[this->_args[i][1]] = i;
      }
    }
  }
  for (std::map<char, int>::iterator it = this->_trackM.begin() ; it != this->_trackM.end() ; ++it) {
    if ((*it).second == -1) {
      return (false);
    }
  }
  return (true);
}

int	Utils::Args::get(char c) const {
  if (this->_trackM.find(c) == this->_trackM.end()) {
    if (this->_track.find(c) != this->_track.end()) {
      return (this->_track.at(c));
    }
  }
  else {
    return (this->_trackM.at(c));
  }
  throw new MyException("Bad argument for Utils::Args::get : key does not exists");
}
