// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef		__GUIG_ALLYMENU_HPP__
# define	__GUIG_ALLYMENU_HPP__

#include	"overlays/OverlayImage.hh"
#include	"overlays/OverlayText.hh"
#include	"overlays/AOverlaySceneManager.hh"
#include	"GUIG/AGUIG.hpp"

namespace GUIG {
  class AllyMenu: public AGUIG, public AOverlaySceneManager {
  private:
    Ogre::Vector2	 _winsize;
    OverlayImage *_background;
    OverlayText	 *_team1Text, *_team2Text;
    std::vector<OverlayText*> _team1, _team2;

  public:
    AllyMenu();
    virtual ~AllyMenu();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void	clear();
    void	addPlayer(const std::string &, int);
  };
}

#endif  /* ___HPP__ */
