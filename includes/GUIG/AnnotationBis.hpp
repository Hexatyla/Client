//
// AnnotationBis.hpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Fri Mar 14 14:52:39 2014 gautier lefebvre
// Last update Mon Mar 31 12:39:53 2014 geoffrey bauduin
//

#ifndef		__GUIG_ANNOTATION_BIS_HPP__
#define		__GUIG_ANNOTATION_BIS_HPP__

#include  "Utils/graphicException.hh"
#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Kernel/ElementRessources.hpp"
#include  "Kernel/Serial.hpp"
#include  "Game/AElement.hpp"
#include  "Converter.hpp"

namespace	GUIG {
  class		AnnotationBis :public AGUIG, public AOverlaySceneManager {
  private:
    unsigned int	_gold, _food, _wood, _ress;
    Kernel::ElementRessources::Type	_ressType;
    OverlayImage	*_bg;
    OverlayText		*_name, *_goldCost, *_foodCost, *_woodCost, *_ressCost, *_coolDown, *_timeCost, *_description;
    std::list<OverlayText*> _requirements;
    Ogre::Vector2	_winsize;

    void	updatePositions();

  public:
    AnnotationBis();
    virtual ~AnnotationBis();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void	clear();
    void	addRequirement(const std::string &, bool);
    void	setGold(unsigned int);
    void	setFood(unsigned int);
    void	setWood(unsigned int);
    void	setRess(unsigned int);
    void	setRessType(Kernel::ElementRessources::Type t);
    void	setCoolDown(const std::string &);
    void	setTime(const std::string &);
    void	update(const Kernel::Serial &, const Game::Player *player);
  };
}

#endif
