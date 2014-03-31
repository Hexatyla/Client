//
// graphicException.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/utils
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Fri Jan 24 15:53:57 2014 Yannick Briffa
// Last update Fri Jan 24 15:56:02 2014 Yannick Briffa
//

#ifndef	__GRAPHICEXCEPTION_HH__
# define __GRAPHICEXCEPTION_HH__

# include	<stdexcept>
# include	<string>

class   graphicException : public std::exception
{
protected:
  std::string   _what;

public:
  graphicException (std::string const &) throw();
  virtual ~graphicException() throw();
  virtual const char* what() const throw();
};

#endif
