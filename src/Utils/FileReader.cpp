//
// FileReader.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 11:14:13 2014 geoffrey bauduin
// Last update Wed Jan 22 11:23:42 2014 geoffrey bauduin
//

#include	<fstream>
#include	"Utils/FileReader.hpp"

FileReader::FileReader(void):
  _content("") {
}

FileReader::~FileReader(void) {}

const std::string	&FileReader::getContent(void) const {
  return (this->_content);
}

void	FileReader::read(const std::string &file) {
  std::ifstream fd(file.c_str());
  if (fd.fail()) {
    throw new FileReader::Exception(std::string("Cannot open ") + file);
  }
  std::getline(fd, this->_content, '\0');
}

FileReader::Exception::Exception(const std::string &what) throw():
  _what(what) {}

FileReader::Exception::~Exception(void) throw() {}

const char	*FileReader::Exception::what(void) const throw() {
  return (this->_what.c_str());
}
