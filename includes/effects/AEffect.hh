//
// AEffect.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:26:13 2014 Yannick Briffa
// Last update Tue Feb 11 09:30:11 2014 Yannick Briffa
//

#ifndef	__AEFFECT_HH__
# define __AEFFECT_HH__

# include	"effects/IEffect.hh"

class	AEffect : public IEffect
{
protected:
  bool		_ended;

public:
  AEffect();
  virtual ~AEffect();

  virtual bool	isEnded() const;
};

#endif
