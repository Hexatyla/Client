// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_CONTROLLER_HPP__
# define  __GUIG_CONTROLLER_HPP__

#include  "scene/AScene.hh"

#include  <algorithm>
#include  "applications/Application.hh"
#include  "effects/MoveOverlay.hh"
#include  "effects/MoveObject.hh"
#include  "effects/Scale.hh"
#include  "effects/Fade.hh"
#include  "overlays/Click.hh"
#include  "overlays/TextBox.hh"

#include  "Protocol/Job.hpp"
#include  "Factory/Protocol.hpp"
#include  "Client/JobController.hpp"
#include  "Network/Manager/Client.hpp"
#include  "Algo/MD5.hpp"
#include  "Protocol/Race.hpp"

#include  "GUIG/Progress.hpp"
#include  "GUIG/Profile.hpp"
#include  "GUIG/Ressource.hpp"
#include  "GUIG/Annotation.hpp"
#include  "GUIG/AnnotationBis.hpp"
#include  "GUIG/MiniMap.hpp"
#include  "GUIG/DayNight.hpp"
#include  "GUIG/AllyMenu.hpp"
#include  "GUIG/Menu.hpp"
#include  "GUIG/Squad.hpp"
#include  "GUIG/ChatBox.hpp"

#include  "Parser/RaceClient.hpp"

#include  "3DElements/Element3DPoolManager.hh"
#include  "3DElements/Element3DContainer.hh"

#include  "Game/Map.hpp"
#include  "Parser/Map.hpp"
#include  "Factory/Game.hpp"
#include  "Game/Controller.hpp"
#include  "Kernel/Config.hpp"
#include  "Protocol/Race.hpp"

#define GUIG_SIZE_MAP_X 20
#define GUIG_SIZE_MAP_Y 20

namespace   GUIG
{
  class Controller : public AScene
  {
  private:
    Controller();
    Controller(Controller const&);

  public:
    bool _moving;
    Controller(Ogre::RenderWindow*);
    virtual ~Controller();
    virtual void createScene();
    virtual bool keyPressed(const OIS::KeyEvent &e);
    virtual bool keyReleased(const OIS::KeyEvent &e);
    virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    virtual bool mouseMoved(const OIS::MouseEvent &e);
    virtual bool updateFrame(const Ogre::FrameEvent &);

  public:
    void  click(std::string const&);
    void  actionClick(const std::string &);
    void  actionClickSpecial(const std::string &);

    // PRIVATE CONTAINER
  public:
    enum actClickAction
    {
      UNKNOWN     = 0,
      CAPATOUNIT,
      CAPATOZONE,
      ATTACKTOZONE,
      ATTACKTOUNIT,
      CREATEBUILDING,
      UNITPATROL
    };

  private:
    Ogre::Light *_soleil;
    std::string fileName;
    bool  inGame, _KC_UP, _KC_DOWN, _KC_LEFT, _KC_RIGHT, _KC_CTRL;
    Parser::Race parserRace;
    Parser::ARace::Container containerRace;
    Element3DPoolManager  elementPoolManager;
    Ogre::Vector2 mousePosition;
    Ogre::Vector2 _mousePressed;
    Ogre::Vector2 _mouseReleased;
    Game::Map *_map;
    std::map<unsigned int, Element3DContainer*>  mapGraph;
    std::map<Kernel::ID::id_t, Game::Player*>        _players;
    Game::Player                      *_player;
    std::map<Kernel::ID::id_t, Game::AElement*> _elements;
    std::map<Kernel::ID::id_t, Element3DContainer*> _elements3D;
    std::map<unsigned int, Game::Team*> teams;
    bool  _UnitIsSelected;
    Kernel::ID::id_t _UnitSelectedId;
    bool  _MB_LEFT;
    bool  _MB_RIGHT;
    bool  _actClick;
    bool  _mapIsInit;
    GUIG::Controller::actClickAction  _actClickAction;
    GUIG::Controller::actClickAction  _actClickActionBis;
    Kernel::Serial _serialAction;
    bool  _actClickModified;
    Kernel::ID::id_t _idPlayerTMP;
    AOverlay *_savTMPhover;
    std::map<OIS::KeyCode, std::vector<Kernel::ID::id_t>> quickSav;

    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> CONTROLLER_FCT;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> minimap_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> ressource_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> progress_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> guigProfile_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> guigSquad_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> element3D_fct;
    std::map<std::string, void (GUIG::Controller::*)(const std::string &)> guigChatbox_fct;
    //annotation
    //daynight

    GUIG::Minimap	*minimap;
    GUIG::Ressource	*ressource;
    GUIG::Progress	*progress;
    GUIG::DayNight	*daynight;
    GUIG::Annotation	*annotation;
    GUIG::AnnotationBis	*annotationbis;
    GUIG::AllyMenu	*allymenu;
    GUIG::Menu		*menu;
    GUIG::Profile	*profile;
    GUIG::Squad		*squad;
    GUIG::ChatBox	*chatbox;

    //  PRIVATE FUNCTION
    private:
      void  drawInterface();
      void  startLoading();
      void  exitGame();
      void  controllerEmpty(const std::string &);
      void  controllerCreateMap();
      void  unitSelectedAttackId(Kernel::ID::id_t);
      void  unitSelectedMoveToPosition(int, int);
      void  harvestUnitSelected(Kernel::ID::id_t id);
      void  unitBuilt(Kernel::ID::id_t);
      void  checkIfCapacity(AOverlay*);
      void  tryToSavGroupUnit(OIS::KeyCode);
      void  tryToSelectGroupUnit(OIS::KeyCode);

    // GUIG_CHATBOX_HPP
    private:
      void  guigChatbox_function(const std::string &);
      void  guigChatbox_input(const std::string &);
    public:
      void	guigChatbox_recvWhisp(const std::string &from, const std::string &msg);
      void	guigChatbox_recvGrpMsg(const std::string &from, const std::string &msg);
      void	guigChatbox_recvMsgGlob(const std::string &from, const std::string &msg);

    // ELEMENT3D_HPP
    private:
      void  element3D_function(const std::string &);
      Kernel::ID::id_t  element3D_findElement(const std::string &);

    // GAME_HPP partial
    private:
      bool  itemExist(Kernel::ID::id_t);
      const Game::Team  *teamExist(unsigned int);
    public:
    // Game
    Game::Player  *game_findPlayer(Kernel::ID::id_t);
    void  game_itemReplace();
    void  game_setRessource(Kernel::ID::id_t,  unsigned int,  unsigned int, unsigned int);
    void  game_createNewPlayer(Kernel::ID::id_t id, unsigned int teamID, const Kernel::Serial & race);
    void  game_changeDayNight(bool);
    void  game_setYouAre(Kernel::ID::id_t);
    void  game_itemCreation(const Kernel::Serial &, Kernel::ID::id_t, double, double, double, int, Kernel::ID::id_t);
    void  game_itemDestruction(Kernel::ID::id_t);
    void  game_itemUpdate(Kernel::ID::id_t, double, double, double, int, unsigned int, unsigned int,
			  unsigned int, unsigned int);
    void  game_objectKeepedByHero(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_objectPutByHero(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_objectPossessedByHero(Kernel::ID::id_t, const std::vector<Kernel::ID::id_t>&);
    void  game_waypointOfItem(Kernel::ID::id_t, double, double, double, double, unsigned int);
    void  game_itemMoving(Kernel::ID::id_t, double, double, double);
    void  game_stopingAction(Kernel::ID::id_t);
    void  game_itemAction(Kernel::ID::id_t, Game::eAction);
    void  game_effectNoApplyOnItem(Kernel::ID::id_t, const Kernel::Serial &);
    void  game_externEffectApplyOnItem(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &);
    void  game_externEffectNotApplyOnItem(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &);
    void  game_effectApplyOnItem(Kernel::ID::id_t, const Kernel::Serial &, double);
    void  game_stanceOfUnit(Kernel::ID::id_t, Game::Stance::Type);
    void  game_unitHasBeenProduct(Kernel::ID::id_t, const Kernel::Serial &);
    void  game_unitPutInProduction(Kernel::ID::id_t, const Kernel::Serial &, unsigned int);
    void  game_unitHasBeenDeletedFromProductionList(Kernel::ID::id_t, const Kernel::Serial &);
    void  game_buildingBuilt(Kernel::ID::id_t);
    void  game_unitStopBuilding(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_unitBuilding(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_unitMoveRessource(Kernel::ID::id_t, unsigned int, unsigned int, unsigned int);
    void  game_unitHarvest(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_unitEndStopingToHarvest(Kernel::ID::id_t);
    void  game_unitWaitToHarvest(Kernel::ID::id_t);
    void  game_unitStopHarvest(Kernel::ID::id_t);
    void  game_unitDeposit(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_playerAmelioration(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &);
    void  game_ameliorationProduct(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &, unsigned int);
    void  game_ameliorationDeletedFromProductionList(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &);
    void  game_ping(Kernel::ID::id_t, double, double);
    void  game_itemAttackItem(Kernel::ID::id_t, Kernel::ID::id_t);
    void  game_itemAttackZone(Kernel::ID::id_t, double, double, double);
    void  game_itemUseCapacityOnZone(Kernel::ID::id_t, double, double, double, const Kernel::Serial &);
    void  game_itemUseCapacityOnItem(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &);
    void  game_effectNotApplyOnItem(Kernel::ID::id_t, const Kernel::Serial &);
    void  game_capacityUsed(Kernel::ID::id_t, const Kernel::Serial &);
    void  game_capacityOnAutoOrNot(Kernel::ID::id_t, const Kernel::Serial &, bool);
    void  game_updateSpot(Kernel::ID::id_t, unsigned int);
    void  game_createSpot(Kernel::ID::id_t, double, double, double, Game::Ressources::Type, unsigned int);

    // GUIGPROFILE_HPP
    private:
      void  guigProfile_function(const std::string &);
      void  guigProfile_clean(const std::string &  = "");
      void  guigProfile_putIcon(Kernel::ID::id_t);
      void  guigProfile_putEffects(Kernel::ID::id_t);
      void  guigProfile_putProductions(Kernel::ID::id_t);
      void  guigProfile_putCapacities(Kernel::ID::id_t);
      void  guigProfile_putObjects(Kernel::ID::id_t);
      void  guigProfile_focus(Kernel::ID::id_t);
      void  guigProfile_unFocus();

      void  guigProfile_capacities(const std::string &);
      void  guigProfile_objects(const std::string &);
      void  guigProfile_effects(const std::string &);
      void  guigProfile_productions(const std::string &);

      void  guigProfile_actionCapaToZone(int, int);
      void  guigProfile_actionCapaToZone(Kernel::ID::id_t);
      void  guigProfile_actionCapaToUnit(Kernel::ID::id_t);
      void  guigProfile_actionAttackToZone(int, int);
      void  guigProfile_actionAttackToZone(Kernel::ID::id_t);
      void  guigProfile_actionAttackToUnit(Kernel::ID::id_t);
      void  guigProfile_actionCreateBuilding(int, int);
      void  guigProfile_actionCreateBuilding(Kernel::ID::id_t);
      void  guigProfile_actionUnitPatrol(int, int);
      void  guigProfile_actionUnitPatrol(Kernel::ID::id_t);
    // GUIGSQUAD_HPP
    private:
      void  guigSquad_function(const std::string &);
      void  guigSquad_round(const std::string &);
      void  guigSquad_shield(const std::string &);
      void  guigSquad_attack(const std::string &);
      void  guigSquad_alert(const std::string &);
      void  guigSquad_cancel(const std::string &);

    // CALLBACK POUR CREER LES JOBS ADEQUATS QUAND TU APPUIES SUR UN BOUTON
  private:
    void	callback_moveItem(Kernel::ID::id_t, double, double, double);                                // OK
    void	callback_moveItems(const std::vector<Kernel::ID::id_t> &, bool, double, double, double);    // AFAIRE

    void	callback_changeUnitStance(Kernel::ID::id_t, Game::Stance::Type);                            // OK
    void	callback_changeUnitsStance(const std::vector<Kernel::ID::id_t> &, Game::Stance::Type);      // OK

    void	callback_useCapacity(Kernel::ID::id_t, const Kernel::Serial &);                             // OK
    void	callback_useCapacityZone(Kernel::ID::id_t, const Kernel::Serial &, double, double, double); // OK
    void	callback_automaticCapacity(Kernel::ID::id_t, const Kernel::Serial &, bool);                 // OK
    void  callback_itemUseCapacity(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &cap);    // OK

    void	callback_createBuilding(const Kernel::Serial &, double, double, double, int);               // OK

    void	callback_stopItemAction(Kernel::ID::id_t);                                                  // OK
    void	callback_setItemAction(Kernel::ID::id_t, Game::eAction);                                    // --
    void	callback_setItemsAction(const std::vector<Kernel::ID::id_t> &, Game::eAction);              // --

    void	callback_produceUnit(Kernel::ID::id_t, const Kernel::Serial &);                             // OK
    void	callback_removeUnitFromProduction(Kernel::ID::id_t, const Kernel::Serial &);                // OK
    void	callback_produceAmelioration(const Kernel::Serial &, const Kernel::Serial &);               // OK
    void	callback_removeAmeliorationFromProduction(const Kernel::Serial &, const Kernel::Serial &);  // OK

    void	callback_heroPickUpObject(Kernel::ID::id_t, Kernel::ID::id_t);                              //
    void	callback_heroReleaseObject(Kernel::ID::id_t, Kernel::ID::id_t, double, double, double);     //

    void	callback_unitBuild(Kernel::ID::id_t, Kernel::ID::id_t);                                     // OK
    void	callback_unitHarvest(Kernel::ID::id_t, Kernel::ID::id_t);                                   // OK
    void	callback_unitsHarvest(const std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t);             // OK
    void	callback_unitsBuild(const std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t);               // OK
    void	callback_unitPatrol(Kernel::ID::id_t, double, double);                                      // OK
    void	callback_unitsPatrol(const std::vector<Kernel::ID::id_t> &, double, double, bool);          // OK

    void	callback_itemAttack(Kernel::ID::id_t, Kernel::ID::id_t);                                    // OK
    void	callback_itemsAttack(const std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t);              // OK

    void	callback_itemAttackZone(Kernel::ID::id_t, double, double, double);                          // OK
    void	callback_itemsAttackZone(const std::vector<Kernel::ID::id_t> &, double, double, double);    // OK


    private:
      // Camera
      void  initCamera();
      void  moveCameraUp();
      void  moveCameraDown();
      void  moveCameraLeft();
      void  moveCameraRight();

  // MENU && MENUALLY
  public:
    void  controller_menuActivate(const std::string & = "");
    void  controller_menuDesactivate(const std::string & = "");
    void  controller_menuallyActivate(const std::string & = "");
    void  controller_menuallyDesactivate(const std::string & = "");
    void  controller_menuSwitch(const std::string & = "");

  // PROGRESS_HPP
  public:
    void  endLoading();
    void  progress_function(const std::string &);
    //RECEIVE
    void  progress_receivePlayerInRoom(const std::string &pseudo, int team, Race::Race, bool ready);
    void  progress_receiveReadyPlayer(const std::string &);
    void  progress_receiveFileExist(const std::string &name);
  private:
    void  progress_loadFile(const std::string &);

  // MINIMAP_HPP
  public:
    void  minimap_function(const std::string &);
    void  minimap_moveLook(const std::string &);
    // RECEIVE

  // BIND BUTTON
  public:
    void		zoomMinimap(char);

  // RESSOURCE_HPP
  public:
    void  ressource_function(const std::string &);
    // RECEIVE

  };
}

#endif  /* !__GUIG_CONTROLLER_HPP */
