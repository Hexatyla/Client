//
// DayNight.hpp for pfa in /home/gautier/pfa
// 
// Made by gautier lefebvre
// Login   <gautier@epitech.net>
// 
// Started on  Tue Mar 11 17:10:01 2014 gautier lefebvre
// Last update Mon Mar 31 12:40:10 2014 geoffrey bauduin
//

#ifndef		__GUIG_DAYNIGHT_HPP__
#define		__GUIG_DAYNIGHT_HPP__

#include  "Utils/graphicException.hh"
#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Protocol/Race.hpp"

namespace	GUIG {
  class		DayNight :public AGUIG, public AOverlaySceneManager {
  private:
    OverlayImage *_imageDay, *_imageNight;
    OverlayText  *_textMenu, *_textTeam;
    bool	_day;

  public:
    DayNight();
    virtual ~DayNight();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void setDate(unsigned int, unsigned int, unsigned int);
    bool	isDay() const;
  };
}

#endif
