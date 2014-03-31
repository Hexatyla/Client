//
// AClick.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb 10 18:10:58 2014 Yannick Briffa
// Last update Mon Feb 10 18:27:51 2014 Yannick Briffa
//

#ifndef	__ICLICK_HH__
# define __ICLICK_HH__

# include	"effects/IEffect.hh"

class	IClick
{
public:
  virtual ~IClick() {}

  virtual IEffect	*effectOnClick() = 0;
};

#endif
