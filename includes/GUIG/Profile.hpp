// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/AGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_PROFIL_HPP__
# define  __GUIG_PROFIL_HPP__

#include  "GUIG/AGUIG.hpp"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "Kernel/ID.hpp"
#include  "Kernel/Serial.hpp"

namespace GUIG {
  class Profile : public AGUIG, public AOverlaySceneManager {
    public:
      struct VectorKernel
      {
        Kernel::Serial    serial;
        Kernel::ID::id_t  id;
        std::string       pathImage;
      };

  private:
    Ogre::Vector2 winsize;

    VectorKernel*	_iconProfil;
    OverlayImage* _ProfilBlank;

    Ogre::Vector2 _sizeProductions;
    Ogre::Vector2 _sizeObjects;
    Ogre::Vector2 _sizeEffects;
    Ogre::Vector2 _sizeCapacities;

    std::vector<GUIG::Profile::VectorKernel*>		_productions;
    std::vector<GUIG::Profile::VectorKernel*>		_objects;
    std::vector<GUIG::Profile::VectorKernel*>	  _effects;
    std::vector<GUIG::Profile::VectorKernel*>	  _capacities;

    std::vector<OverlayImage*>      _ImageCapacitiesBlank;
    std::vector<OverlayImage*>      _ImageObjectsBlank;
    std::vector<OverlayImage*>      _ImageEffectsBlank;
    std::vector<OverlayImage*>      _ImageProductionsBlank;

    Ogre::Vector2*                  _PositionProfileIcon;
    std::vector<Ogre::Vector2*>     _PositionCapacities;
    std::vector<Ogre::Vector2*>     _PositionObjects;
    std::vector<Ogre::Vector2*>     _PositionEffects;
    std::vector<Ogre::Vector2*>     _PositionProductions;

  public:
    Profile();
    virtual ~Profile();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  private:
    void  CreateAndPosItem(const GUIG::Profile::VectorKernel &, const Ogre::Vector2 &,
                      const Ogre::Vector2 &, const std::string &, unsigned int);
    void  deleteGraphicalItem(const GUIG::Profile::VectorKernel &, unsigned int pos, const std::string &name);
    void  clearProductions();
    void  clearObjects();
    void  clearCapacities();
    void  clearEffects();
    void  clearIcons();

  public:
    void	clear();

    void  profileSetIcon(const std::string &file, Kernel::ID::id_t, const Kernel::Serial&);
    // Production gestion
    void	productionsElementPush(Kernel::ID::id_t, const Kernel::Serial &, const std::string &);
    bool	productionsElementPop();
    void  productionsElementDelete(Kernel::ID::id_t);
    bool	productionsElementDelete(const Kernel::Serial &);
    void	productionsElementDeleteAll(const Kernel::Serial &);
    void  productionsElementDeleteAt(unsigned int);
    Kernel::Serial  *getSerialToProductionElement(unsigned int);
    Kernel::ID::id_t      *getIdToProductionElement(unsigned int);
    unsigned int getProductionsSize();
    // object gestion
    void  objectsElementPush(Kernel::ID::id_t, const Kernel::Serial &, const std::string &);
    bool  objectsElementPop();
    void  objectsElementDelete(Kernel::ID::id_t);
    bool  objectsElementDelete(const Kernel::Serial &);
    void  objectsElementDeleteAll(const Kernel::Serial &);
    void  objectsElementDeleteAt(unsigned int);
    Kernel::Serial  *getSerialToObjectElement(unsigned int);
    Kernel::ID::id_t      *getIdToObjectElement(unsigned int);
    unsigned int getObjectsSize();
    // Capacities gestion
    void  capacitiesElementPush(Kernel::ID::id_t, const Kernel::Serial &, const std::string &);
    bool  capacitiesElementPop();
    void  capacitiesElementDelete(Kernel::ID::id_t);
    bool  capacitiesElementDelete(const Kernel::Serial &);
    void  capacitiesElementDeleteAll(const Kernel::Serial &);
    void  capacitiesElementDeleteAt(unsigned int);
    Kernel::Serial  *getSerialToCapacityElement(unsigned int);
    Kernel::ID::id_t      *getIdToCapacityElement(unsigned int);
    unsigned int getCapacitiesSize();
    // Effects gestion
    void  effectsElementPush(Kernel::ID::id_t, const Kernel::Serial &, const std::string &);
    bool  effectsElementPop();
    void  effectsElementDelete(Kernel::ID::id_t);
    bool  effectsElementDelete(const Kernel::Serial &);
    void  effectsElementDeleteAll(const Kernel::Serial &);
    void  effectsElementDeleteAt(unsigned int);
    Kernel::Serial    *getSerialToEffectElement(unsigned int);
    Kernel::ID::id_t        *getIdToEffectElement(unsigned int);
    unsigned int getEffectsSize();
  };
}

#endif  /* ___HPP__ */
