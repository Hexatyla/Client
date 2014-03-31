//
// Squad.hpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Wed Mar 19 14:01:57 2014 gautier lefebvre
// Last update Tue Mar 25 11:16:52 2014 Gautier Lefebvre
//

#ifndef		__GUIG_SQUAD_HPP__
#define		__GUIG_SQUAD_HPP__

#include	"GUIG/AGUIG.hpp"
#include	"overlays/AOverlaySceneManager.hh"
#include	"overlays/OverlayImage.hh"
#include	"overlays/OverlayText.hh"
#include	"Kernel/ID.hpp"
#include	"Kernel/Serial.hpp"
#include	"Game/AElement.hpp"

namespace	GUIG {
  class		Squad :public AGUIG, public AOverlaySceneManager {
  private:
    struct	unitInfo {
      AOverlay*	unit;
      AOverlay* background;
      Kernel::ID::id_t id;
      std::string image;
      unsigned int life;
      Kernel::Serial serial;

      unitInfo();
    };

    Ogre::Vector2		_winsize;
    std::vector<OverlayImage*>	_actions;
    std::vector<OverlayImage*>	_unitsBlank;
    std::vector<unitInfo>	_units;
    std::vector<Kernel::ID::id_t> _idUnits;

    std::string	defineButtonName(const Kernel::Serial&, unsigned int) const;
    std::string defineBackgroundName(unsigned int, unsigned int, std::string &) const;
    void	definePosition(unsigned int, int &, int &) const;
    unsigned int getCaseByID(Kernel::ID::id_t) const;
    void	updatePositions();
    void	emptyCase(unsigned int);
    void	setUnit(unsigned int, const std::string &, Kernel::ID::id_t, const Kernel::Serial &serial);

  public:
    Squad();
    virtual ~Squad();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void	clear();
    void	removeUnit(Kernel::ID::id_t);
    bool	addUnit(const std::string &, Kernel::ID::id_t, const Kernel::Serial &);
    void	setLife(Kernel::ID::id_t, unsigned int);
    Kernel::ID::id_t getIdOfCase(unsigned int c);
    const std::vector<Kernel::ID::id_t> &get_idUnits();
    void	update(const std::map<Kernel::ID::id_t, Game::AElement *> &);
  };
}

#endif
