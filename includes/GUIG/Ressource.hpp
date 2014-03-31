// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_RESSOURCE_HPP__
# define  __GUIG_RESSOURCE_HPP__

#include  "Utils/graphicException.hh"
#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Protocol/Race.hpp"

namespace GUIG {
  class Ressource :public AGUIG, public AOverlaySceneManager {
  private:
    unsigned int  _gold, _wood, _food, _maxfood;
    Race::Race	  _race;
    OverlayImage *_race1Logo, *_race2Logo, *_race3Logo, *_woodLogo, *_goldLogo;
    OverlayText  *_foodText, *_woodText, *_goldText;

  public:
    Ressource();
    virtual ~Ressource();
  
  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void setGold(unsigned int);
    void setWood(unsigned int);
    void setFood(unsigned int);
    void setMaxFood(unsigned int);
    void setRace(Race::Race );
  };
}

#endif  /* __GUI_RESSOURCE_HPP__ */
