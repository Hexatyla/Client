// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_MENU_HPP__
# define  __GUIG_MENU_HPP__

#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/Button.hh"

namespace GUIG {
  class Menu :public AGUIG, public AOverlaySceneManager {
  private:
    OverlayImage *_background;
    Button	 *_exit;
    Button	 *_back;
    
  public:
    Menu();
    virtual ~Menu();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();
  };
}

#endif  /* ___HPP__ */
