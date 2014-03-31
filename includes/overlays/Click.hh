//
// AClick.hh for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb 10 18:10:58 2014 Yannick Briffa
// Last update Mon Feb 10 18:28:21 2014 Yannick Briffa
//

#ifndef	__CLICK_HH__
# define __CLICK_HH__

# include	"overlays/IClick.hh"

class	Click : public IClick
{
public:
  Click();
  virtual ~Click();

  virtual IEffect	*effectOnClick();
};

#endif
