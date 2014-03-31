//
// AEffect.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:27:21 2014 Yannick Briffa
// Last update Tue Feb 11 09:30:43 2014 Yannick Briffa
//

# include	"effects/AEffect.hh"

AEffect::AEffect()
  : _ended(false)
{
}

AEffect::~AEffect()
{
}

bool		AEffect::isEnded() const
{
  return _ended;
}
