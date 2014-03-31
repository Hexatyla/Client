//
// IRepeatable.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/move
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 22:50:24 2014 Yannick Briffa
// Last update Tue Feb 11 09:47:03 2014 Yannick Briffa
//

#ifndef __IREPEATABLE_HH__
# define __IREPEATABLE_HH__

class	IRepeatable
{
public:
  virtual ~IRepeatable() {}

  virtual bool	isRepeatable() const = 0;
  virtual void	setRepeatable(bool) = 0;
};

#endif
