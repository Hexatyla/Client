// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Controller.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __MAINHEXATYLA_HPP__
# define  __MAINHEXATYLA_HPP__

# include	"overlays/AOverlaySceneManager.hh"

class MainHexatyla : public AOverlaySceneManager
{
  public:
    MainHexatyle();
    virtual ~MainHexatyle();

    virtual void		init(unsigned int, unsigned int);
};

#endif /* !__MAINHEXATYLA_HPP__ */
