// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_ANNOTATION_HPP__
# define  __GUIG_ANNOTATION_HPP__

#include  "utils/graphicException.hh"
#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Kernel/ElementRessources.hpp"
#include  "Game/AElement.hpp"

namespace GUIG {
  class Annotation :public AGUIG, public AOverlaySceneManager {
  private:
    std::string	_name;
    unsigned int _speed;
    double	_range, _rangeBonus;
    unsigned int _attack;
    int		_attackBonus;
    unsigned int _armor;
    int		_armorBonus;
    unsigned int _hp;
    unsigned int _hpmax;
    int		_hpmaxBonus;
    unsigned int _ress;
    Kernel::ElementRessources::Type _elementType;
    OverlayImage *_bg, *_shield, *_gun;
    OverlayText  *_nameText;
    OverlayText  *_speedText;
    OverlayText  *_rangeText;
    OverlayText  *_attackText;
    OverlayText  *_armorText;
    OverlayText  *_hpText;
    OverlayText  *_ressText;
    OverlayText	 *_ressourcesCarryText;
    OverlayText  *_description;
    OverlayText	*_building;

  private:
    void	addBonus(std::string &, Ogre::ColourValue &, int, const std::string &) const;

  public:
    Annotation();
    virtual ~Annotation();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void setName(const std::string &);

    void setSpeed(unsigned int);

    void setRange(double);
    void setRangeBonus(double);

    void setAttack(unsigned int);
    void setAttackBonus(int);

    void setArmor(unsigned int);
    void setArmorBonus(int);

    void setHP(unsigned int);
    void setHPMax(unsigned int);
    void setHPMaxBonus(int);

    void setRess(unsigned int);

    void setRessType(Kernel::ElementRessources::Type);

    void update(const Game::AElement *);
    void	hideAll();
    void	showAll();
  };
}

#endif  /* ___HPP__ */
