//
// ARepeatable.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/effects
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Feb 11 09:45:37 2014 Yannick Briffa
// Last update Tue Feb 11 09:51:04 2014 Yannick Briffa
//

#ifndef __AREPEATABLE_HH__
# define __AREPEATABLE_HH__

# include	"effects/IRepeatable.hh"

class	ARepeatable : public IRepeatable
{
private:
  ARepeatable();

protected:
  bool	_repeatable;

public:
  ARepeatable(bool);
  virtual ~ARepeatable();

  virtual bool	isRepeatable() const;
  virtual void	setRepeatable(bool);
};

#endif
