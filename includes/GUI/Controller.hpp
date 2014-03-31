// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Controller.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_CONTROLLER_HPP__
# define  __GUI_CONTROLLER_HPP__

#include  "GUI/Convers.hpp"
#include  "GUI/Core.hpp"
#include  "GUI/Friends.hpp"
#include  "GUI/Group.hpp"
#include  "GUI/Popup.hpp"
#include  "GUI/Profile.hpp"
#include  "GUI/Race.hpp"
#include  "GUI/Setting.hpp"
#include  "GUI/SignInUp.hpp"
#include  "GUI/Tooltip.hpp"
#include  "scene/AScene.hh"

#include	<algorithm>
#include	"applications/Application.hh"
#include	"effects/MoveOverlay.hh"
#include	"effects/MoveObject.hh"
#include	"effects/Scale.hh"
#include	"effects/Fade.hh"
#include	"overlays/Click.hh"
#include	"overlays/TextBox.hh"

#include  "Protocol/Job.hpp"
#include  "Factory/Protocol.hpp"
#include  "Client/JobController.hpp"
#include  "Network/Manager/Client.hpp"
#include  "Algo/MD5.hpp"
#include  "Protocol/Race.hpp"

/// A DELETE
#include  "GUIG/Ressource.hpp"

namespace GUI
{
  class Controller : public AScene
  {
    enum PARTIAL_GUI
    {
      CONVERS = 0,
      CORE,
      FRIENDS,
      GROUP,
      POPUP,
      PROFILE,
      RACE,
      SETTING,
      SIGNINUP,
    };

    private:
      GUI::Convers   *convers;
      GUI::Core      *core;
      GUI::Friends   *friends;
      GUI::Group     *group;
      GUI::Popup     *popup;
      GUI::Popup     *error;
      GUI::Profile   *profile;
      GUI::Race      *race;
      GUI::Setting   *setting;
      GUI::SignInUp  *sign;
      GUI::Tooltip   *tooltip;
      GUIG::Ressource *guig_ressource;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> CORE_FCT;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> core_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> convers_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> friends_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> group_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> popup_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> profile_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> race_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> setting_fct;
      std::map<std::string, void (GUI::Controller::*)(std::string const&)> signinup_fct;
      bool launchGame;
      bool  _MB_LEFT, _MB_RIGHT;

    public:
      virtual bool		updateFrame(const Ogre::FrameEvent &);

    private:
      std::vector<GUI::Controller::PARTIAL_GUI> stack;
      std::vector<GUI::Tooltip*> savTooltip;

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

    public:
      void  click(std::string const&);
      void  empty_click(std::string const&);
      // __CORE_HPP__
      void  core_function(std::string const&);
      void  core_cancelGame(std::string const&);
      void  core_createGroup(std::string const&);
      void  core_connectOnline(std::string const&);
      void  core_play(std::string const&);
      void  core_launch(std::string const&);
      void  core_launchSpeed3(std::string const&);
      void  core_launchSpeed2(std::string const&);
      void  core_launchSpeed1(std::string const&);
      void  core_back(std::string const&);
      void  core_setting(std::string const&);
      void  core_valideCreateGroup(std::string const&);
      void  core_receiveCreatingGroupValidate(const std::string &);
      void  core_receiveStartGame(const std::string&);
      void  core_gameLoading(const std::string&);
      void  core_receiveStopGame(const std::string&);
    private:
      void  core_moveBg(unsigned int);
      void  core_resetBg();

    public:
      // __CONVERS_HPP__
      void  convers_function(std::string const&);
      void  convers_closeBubble(std::string const&);
      void  convers_hiddenByPseudo(std::string const&);
      void  convers_selectedBox(std::string const&);
      void  convers_moveUp(std::string const&);
      void  convers_moveDown(std::string const&);
      void  convers_new(std::string const&);
      void  convers_old(std::string const&);
      void  convers_sendMessage(std::string const&);
      void  convers_input(const std::string &);
      void  convers_receiveMessage(std::string const&, const std::string &, const std::string&);

    public:
      // __FRIENDS_HPP__
      void  friends_function(std::string const&);
      void  friends_infoFriend(std::string const&);
      void  friends_rmFriend(std::string const&);
      void  friends_addFriend(std::string const&);
      void  friends_moveUp(std::string const&);
      void  friends_moveDown(std::string const&);
      void  friends_mess(std::string const&);
      void  friends_ingame(std::string const&);
      void  friends_sendAddFriend(std::string const&);
      void  friends_sendDeleteFriend(std::string const&);
      void  friends_receiveRequestFriend(const std::string &act);
      void  friends_receiveAddFriend(const std::string &act, User::Status stat);
      void  friends_receiveDeleteFriend(const std::string &act);
      void  friends_receiveUpdateFriend(const std::string &act, User::Status);
      void  friends_answerRequestFriend(const std::string &act);

    public:
      // __GROUP_HPP__
      void  group_function(std::string const&);
      void  group_addPlayerToGame(std::string const&);
      void  group_sendAddPlayerToGame(std::string const&);
      void  group_removePlayerToGame(std::string const&);
      void  group_sendMessage(std::string const&);
      void  group_updateUser(std::string const&);
      void  group_deleteUser(std::string const&);
      void  group_addingPlayerToGame(std::string const&);
      void  group_removingPlayerToGame(std::string const&);
      void  group_input(const std::string&);
      // --------------------------------
      void  group_receiveMessage(std::string const&, std::string const&);
      void  group_receiveRequestGroup(std::string const&);
      void  group_choiceAnswer(std::string const&);
      void  group_closeGroup(std::string const&);
      void  group_receiveLeftPlayer(const std::string&);
      void  group_receiveMemberChangedRace(const std::string &, ::Race::Race);
      void  group_receiveNewMemberGroup(const std::string&, ::Race::Race);

    public:
      // __POPUP_HPP__
      void  popup_function(std::string const&);
      void  popup_accept(std::string const&);
      void  popup_cancel(std::string const&);
      void  popup_validate(std::string const&);
      void  popup_exit(std::string const&);
      void  popup_input(std::string const&);
    private:
      void  popup_close();

    public:
      // __PROFILE_HPP__
      void  profile_function(std::string const&);
      void  profile_updateMyUserData(std::string const&);
      void  profile_updateUserData(std::string const&);
      void  profile_exit(std::string const&);

    public:
      // __RACE_HPP__
      void  race_function(std::string const&);
      void  race_setRace(std::string const&);

    public:
      // __SETTING_HPP__
      void  setting_function(std::string const&);
      void  setting_exit(std::string const&);

    public:
      // __SIGNINUP_HPP__
      void  signinup_function(std::string const&);
      void  signinup_validate(std::string const&);
      void  signinup_signIn(std::string const&);
      void  signinup_signUp(std::string const&);
      void  signinup_exit(std::string const&);
      void  signinup_UPsuccessfull(std::string const&);
      void  signinup_UPerror(std::string const&);
      void  signinup_INsuccessfull(std::string const&);
      void  signinup_INerror(std::string const&);
      void  signinup_input(std::string const&);

    private:
      bool  can_access_race();
      bool  can_access_core();
      bool  can_access_convers();
      bool  can_access_friends();
      bool  can_access_group();
      bool  can_access_popup();
      bool  can_access_profile();
      bool  can_access_setting();
      bool  can_access_signinup();
  };
}

#endif  /* !__GUI_CONTROLLER_HPP__ */
