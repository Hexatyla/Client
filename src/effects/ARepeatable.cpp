//
// ARepeatable.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:49:17 2014 Yannick Briffa
// Last update Tue Feb 11 09:52:07 2014 Yannick Briffa
//

#include	"effects/ARepeatable.hh"

ARepeatable::ARepeatable(bool repeatable)
  : _repeatable(repeatable)
{
}

ARepeatable::~ARepeatable()
{
}

bool		ARepeatable::isRepeatable() const
{
  return _repeatable;
}

void		ARepeatable::setRepeatable(bool repeat)
{
  _repeatable = repeat;
}
