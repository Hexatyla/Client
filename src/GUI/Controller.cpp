// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Controller.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26


#include  <map>
#include  "GUI/Controller.hpp"

#ifndef DEBUG_CONTROLLER
  # include  <iostream>
  static void  function_debug(const std::string& file, const std::string& fct, int line, bool access)
    {
      std::cout << "\033[35m" << file << "\033[0m" << " " <<  line << "\t- " << fct;
      if (!access)
        std::cout << " : " << "\033[31m" << "Access denied" << "\033[0m";
      std::cout << std::endl;
    }
  # define  __CALL_FUNCTION_DEBUG__(file, fct, line, trb) function_debug(file, fct, line, trb)
#else
  # define  __CALL_FUNCTION_DEBUG__(file, fct, line, trb)
#endif

GUI::Controller::Controller(Ogre::RenderWindow *win) :
        AScene(std::string("MenuScene"), win, Ogre::ColourValue(0.08,0.08,0.08)), launchGame(false),
        _MB_LEFT(true), _MB_RIGHT(false)
{
  stack.push_back(GUI::Controller::CORE);
  CORE_FCT["empty_click"]         = &GUI::Controller::empty_click;

  CORE_FCT["core"] = &GUI::Controller::core_function;
  core_fct["cancelGame"]     = &GUI::Controller::core_cancelGame;
  core_fct["createGroup"]    = &GUI::Controller::core_createGroup;
  core_fct["connectOnline"]  = &GUI::Controller::core_connectOnline;
  core_fct["play"]           = &GUI::Controller::core_play;
  core_fct["launch"]         = &GUI::Controller::core_launch;
  core_fct["launchSpeed3"]   = &GUI::Controller::core_launchSpeed3;
  core_fct["launchSpeed2"]   = &GUI::Controller::core_launchSpeed2;
  core_fct["launchSpeed1"]   = &GUI::Controller::core_launchSpeed1;
  core_fct["back"]           = &GUI::Controller::core_back;
  core_fct["setting"]        = &GUI::Controller::core_setting;
  core_fct["valideCreateGroup"]    = &GUI::Controller::core_valideCreateGroup;

  CORE_FCT["convers"]             = &GUI::Controller::convers_function;
  convers_fct["closeBubble"]      = &GUI::Controller::convers_closeBubble;
  convers_fct["hiddenByPseudo"]   = &GUI::Controller::convers_hiddenByPseudo;
  convers_fct["selectedBox"]      = &GUI::Controller::convers_selectedBox;
  convers_fct["moveUp"]           = &GUI::Controller::convers_moveUp;
  convers_fct["moveDown"]         = &GUI::Controller::convers_moveDown;
  convers_fct["new"]              = &GUI::Controller::convers_new;
  convers_fct["old"]              = &GUI::Controller::convers_old;
  convers_fct["sendMessage"]      = &GUI::Controller::convers_sendMessage;
  convers_fct["input"]            = &GUI::Controller::convers_input;

  CORE_FCT["friends"]             = &GUI::Controller::friends_function;
  friends_fct["infoFriend"]       = &GUI::Controller::friends_infoFriend;
  friends_fct["rmFriend"]         = &GUI::Controller::friends_rmFriend;
  friends_fct["addFriend"]        = &GUI::Controller::friends_addFriend;
  friends_fct["moveUp"]           = &GUI::Controller::friends_moveUp;
  friends_fct["moveDown"]         = &GUI::Controller::friends_moveDown;
  friends_fct["mess"]             = &GUI::Controller::friends_mess;
  friends_fct["ingame"]           = &GUI::Controller::friends_ingame;
  friends_fct["sendAddFriend"]    = &GUI::Controller::friends_sendAddFriend;
  friends_fct["sendDeleteFriend"] = &GUI::Controller::friends_sendDeleteFriend;
  friends_fct["answerRequestFriend"] = &GUI::Controller::friends_answerRequestFriend;

  CORE_FCT["group"]                 = &GUI::Controller::group_function;
  group_fct["addPlayerToGame"]      = &GUI::Controller::group_addPlayerToGame;
  group_fct["sendAddPlayerToGame"]  = &GUI::Controller::group_sendAddPlayerToGame;
  group_fct["removePlayerToGame"]   = &GUI::Controller::group_removePlayerToGame;
  group_fct["sendMessage"]          = &GUI::Controller::group_sendMessage;
  group_fct["updateUser"]           = &GUI::Controller::group_updateUser;
  group_fct["deleteUser"]           = &GUI::Controller::group_deleteUser;
  group_fct["input"]                = &GUI::Controller::group_input;
  group_fct["choiceAnswer"]         = &GUI::Controller::group_choiceAnswer;

  CORE_FCT["popup"]           = &GUI::Controller::popup_function;
  popup_fct["accept"]         = &GUI::Controller::popup_accept;
  popup_fct["cancel"]         = &GUI::Controller::popup_cancel;
  popup_fct["validate"]       = &GUI::Controller::popup_validate;
  popup_fct["exit"]           = &GUI::Controller::popup_exit;
  popup_fct["input"]          = &GUI::Controller::popup_input;

  CORE_FCT["profile"]               = &GUI::Controller::profile_function;
  profile_fct["updateMyUserData"]   = &GUI::Controller::profile_updateMyUserData;
  profile_fct["updateUserData"]     = &GUI::Controller::profile_updateUserData;
  profile_fct["exit"]               = &GUI::Controller::profile_exit;

  CORE_FCT["race"]              = &GUI::Controller::race_function;
  race_fct["setRace"]           = &GUI::Controller::race_setRace;

  CORE_FCT["setting"]           = &GUI::Controller::setting_function;
  setting_fct["exit"]           = &GUI::Controller::setting_exit;

  CORE_FCT["signinup"]        = &GUI::Controller::signinup_function;
  signinup_fct["validate"]    = &GUI::Controller::signinup_validate;
  signinup_fct["signIn"]      = &GUI::Controller::signinup_signIn;
  signinup_fct["signUp"]      = &GUI::Controller::signinup_signUp;
  signinup_fct["exit"]        = &GUI::Controller::signinup_exit;
  signinup_fct["input"]       = &GUI::Controller::signinup_input;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

#include	<unistd.h>
#include	<sys/types.h>

bool			GUI::Controller::updateFrame(const Ogre::FrameEvent &evt)
{
  bool ret = true;

  for (auto it : _listMove)
    ret = ((it)->update(evt) == false ? false : ret);
  clearListMove();
  Protocol::Job *job = NULL;
  while ((job = Network::Manager::Client::getInstance()->getJob()))
  {
    std::cout << "Job : " << *job << std::endl;
    Client::JobController::getInstance()->doJob(job, this);
    if (launchGame)
      return (true);
  }
  if (core->gameIsStarting())
  {
    core->draw();
  }
  return (true);
}

void    GUI::Controller::click(std::string const& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (CORE_FCT.find(prec) != CORE_FCT.end())
  {
    (this->*CORE_FCT[prec])(next);
  }
  else
  {
    std::cout << "\t GUI::Controller::click : (not found) [" << name << "]" << std::endl;
   (this->*CORE_FCT["empty_click"])(prec);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void    GUI::Controller::createScene()
{
  _sceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.8));

  convers = new Convers();
  _overlayManagerMap["Convers"] = convers;
  _overlayManagerMap["Convers"]->init(_window->getWidth(), _window->getHeight());

  core = new Core();
  _overlayManagerMap["Core"] = core;
  _overlayManagerMap["Core"]->init(_window->getWidth(), _window->getHeight());

  friends = new Friends();
  _overlayManagerMap["Friends"] = friends;
  _overlayManagerMap["Friends"]->init(_window->getWidth(), _window->getHeight());

  group = new Group();
  _overlayManagerMap["Group"] = group;
  _overlayManagerMap["Group"]->init(_window->getWidth(), _window->getHeight());

  popup = new Popup("pop", 25);
  _overlayManagerMap["Popup"] = popup;
  _overlayManagerMap["Popup"]->init(_window->getWidth(), _window->getHeight());

  error = new Popup("Error", 25);
  _overlayManagerMap["Error"] = error;
  _overlayManagerMap["Error"]->init(_window->getWidth(), _window->getHeight());

  profile = new Profile();
  _overlayManagerMap["Profile"] = profile;
  _overlayManagerMap["Profile"]->init(_window->getWidth(), _window->getHeight());

  race = new Race();
  _overlayManagerMap["Race"] = race;
  _overlayManagerMap["Race"]->init(_window->getWidth(), _window->getHeight());

  setting = new Setting();
  _overlayManagerMap["Setting"] = setting;
  _overlayManagerMap["Setting"]->init(_window->getWidth(), _window->getHeight());

  sign = new SignInUp();
  _overlayManagerMap["SignInUp"] = sign;
  _overlayManagerMap["SignInUp"]->init(_window->getWidth(), _window->getHeight());

  tooltip = new Tooltip();
  _overlayManagerMap["Tooltip"] = tooltip;
  _overlayManagerMap["Tooltip"]->init(_window->getWidth(), _window->getHeight());


  //friends->infoFriend("I", GUI::Activity::IGAME);
  //group->playerJoin("DDP", GUI::R2);
  _overlayManagerMap["SignInUp"]->setVisible(false);
  _overlayManagerMap["Tooltip"]->setVisible(false);
  _overlayManagerMap["Friends"]->setVisible(false);
  _overlayManagerMap["Convers"]->setVisible(false);
  _overlayManagerMap["Group"]->setVisible(false);
  _overlayManagerMap["Popup"]->setVisible(false);
  _overlayManagerMap["Error"]->setVisible(false);
  _overlayManagerMap["Profile"]->setVisible(false);
  _overlayManagerMap["Race"]->setVisible(false);
  _overlayManagerMap["Setting"]->setVisible(false);
  core->setType(GUI::Core::HOME);
  //sign->setVisible(true);
  _currentInput = NULL;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

bool GUI::Controller::keyPressed(const OIS::KeyEvent &e)
{
  static unsigned int i = 0;

  if (e.key == OIS::KC_ESCAPE)
    Application::getInstance()->exit();
  else if (e.key == OIS::KC_F1)
    this->signinup_UPsuccessfull("");// popup->setType(GUI::Popup::INPUT, "Enter a Pseudo :");
  else if (e.key == OIS::KC_F2)
    ;
  else if (e.key == OIS::KC_F3)
    Application::getInstance()->setViewport("GameScene");
  else if (e.key == OIS::KC_F4)
    Application::getInstance()->setViewport("MenuScene");
  else if (e.key == OIS::KC_F6)
    {
      GUIG::Minimap *ptr = dynamic_cast<GUIG::Minimap *>(_overlayManagerMap["minimap"]);
      (*ptr)++;
    }
  else if (e.key == OIS::KC_F7)
    {
      GUIG::Minimap *ptr = dynamic_cast<GUIG::Minimap *>(_overlayManagerMap["minimap"]);
      (*ptr)--;
    }
  else if (e.key == OIS::KC_RETURN)
  {
    if (_currentInput)
    {
      std::cout <<  _currentInput->getName() << std::endl;
		  _currentInput->unfocus();
      const std::string &name = _currentInput->getName();
      _currentInput = NULL;
      this->click(name);
    }
  }
  else if (_currentInput && !_currentInput->keyPressed(e))
  {
    _currentInput = NULL;
  }
  return true;
}

bool	GUI::Controller::keyReleased(const OIS::KeyEvent &e)
{
  if (_currentInput && !_currentInput->keyReleased(e))
    _currentInput = NULL;
  return true;
}

bool	GUI::Controller::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  if (_currentInput) {
    _currentInput->unfocus();
    _currentInput = NULL;
  }

  pickFirstObject3DOnClick(e);
  for(std::map<std::string, AOverlaySceneManager*>::iterator it = _overlayManagerMap.begin();
      it != _overlayManagerMap.end(); ++it)
      {
        if (it->second)
	      {
	        std::vector<AOverlay *> ptr = (it->second)->getOverlayAt(e.state.X.abs, e.state.Y.abs);

	        for (std::vector<AOverlay *>::iterator it2 = ptr.begin(); it2 != ptr.end(); ++it2)
	        {
	          AOverlay *itr = *it2;
	          if (IClick *tmp = dynamic_cast<IClick *>(itr))
		          if (!itr->isLocked() && itr->isInside(e.state.X.abs, e.state.Y.abs))
		          {
		            addEffect(tmp->effectOnClick());
		          }
	          if (!_currentInput)
		          if (InputText *tmp = dynamic_cast<InputText *>(itr))
		          {
		            _currentInput = tmp;
		            _currentInput->focus();
		          }
	          executeSubscribe(itr);
	        }
	      }
      }
  _moving = !_listMove.empty();
  return true;
}

bool	GUI::Controller::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
  pickFirstObject3DOnClick(e);
  if (id == OIS::MB_Left)
  {
    _MB_LEFT = true;
    _MB_RIGHT = false;
  }
  else
  {
    _MB_LEFT = false;
    _MB_RIGHT = true;
  }
  for(std::map<std::string, AOverlaySceneManager*>::iterator it = _overlayManagerMap.begin();
      it != _overlayManagerMap.end(); ++it)
      {
        if (it->second)
	      {
        if (it->second)
        {
	        std::vector<AOverlay *> ptr = (it->second)->getOverlayAt(e.state.X.abs, e.state.Y.abs);
	        for (std::vector<AOverlay *>::iterator it2 = ptr.begin(); it2 != ptr.end(); ++it2)
	        {
	          AOverlay *itr = *it2;
	          if (IClick *tmp = dynamic_cast<IClick *>(itr))
		          if (itr->isInside(e.state.X.abs, e.state.Y.abs))
		          {
		            this->click(itr->getName());
		          }
	        }
        }
	      }
      }
  return true;
}

bool	GUI::Controller::mouseMoved(const OIS::MouseEvent &e)
{
  for(std::map<std::string, AOverlaySceneManager*>::iterator it = _overlayManagerMap.begin();
      it != _overlayManagerMap.end(); ++it)
  {
    if (it->second)
      {
        std::vector<AOverlay *>	ptr = (it->second)->getOverlayAt(e.state.X.abs, e.state.Y.abs);

        if (ptr.size() != 1 && _currentOn)
        {
	        _currentOn->reinitZOrder();
	        _currentOn = NULL;
        }
        else if (ptr.size() == 1)
        {
	        if (_currentOn && _currentOn != ptr.front())
	          _currentOn->reinitZOrder();
	        if (!ptr.front()->isLocked())
	        {
	          _currentOn = ptr.front();
	          _currentOn->changeZOrder(2);
            break;
	        }
        }
     }
    else
    {
      std::cout << "no" <<std::endl;
    }
  }
  return (AScene::mouseMoved(e));
}

GUI::Controller::~Controller()
{
  delete convers;
  delete core;
  delete friends;
  delete group;
  delete popup;
  delete race;
  delete setting;
  delete sign;
#ifndef DEBUG_CONTROLLER
  std::cout << "\t GUI::Controller - Destruction" << std::endl;
#endif
}

// __EMPTY_HPP__

void  GUI::Controller::empty_click(const std::string& act)
{
  // vider tooltip
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

// __CORE_HPP__

bool  GUI::Controller::can_access_core()
{
  return (stack.back() != GUI::Controller::POPUP && stack.back() != GUI::Controller::SIGNINUP &&
          stack.back() != GUI::Controller::PROFILE && stack.back() != GUI::Controller::SETTING);
}

void  GUI::Controller::core_moveBg(unsigned int z)
{
  core->moveBlackScreen(z);
}

void  GUI::Controller::core_resetBg()
{
  this->core_moveBg(1);
}

void  GUI::Controller::core_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (core_fct.find(prec) != core_fct.end())
  {
    (this->*core_fct[prec])(next);
  }
}

void GUI::Controller::core_cancelGame(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->cancelGame();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_createGroup(const std::string& act)
{
  bool trb = false;
  if (can_access_core() && !group->run)
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::INPUT, "Invite your mate");
    popup->setAnswer("validate", "core_valideCreateGroup");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::core_valideCreateGroup(const std::string& act)
{
  bool trb = false;
  if (can_access_core() && !group->run)
  {
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->addPlayerInGroup(popup->getInput());
    Network::Manager::Client::getInstance()->push(job);
/*
    core->createGroup();
    group->run = true;
    group->initFct(core->getUser(), core->getUser(), true, GUI::ALEA);
    group->setVisible(true);
    */
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::core_receiveCreatingGroupValidate(const std::string &act)
{
  bool trb = true;
  if (group->run == false)
  {
    core->createGroup();
    group->run = true;
    group->initFct(core->getUser(), act, true, GUI::ALEA);
    group->setVisible(true);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_connectOnline(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->connectOnline();
    sign->setVisible(true);
    stack.push_back(GUI::Controller::SIGNINUP);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_play(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->play();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_launch(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->launch();
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    if (group->run == false)
      job->quicklaunch(Room::ONEVSONE);
    else
    {
      if (group->size == 1)
        job->quicklaunch(Room::ONEVSONE);
      else if (group->size == 2)
        job->quicklaunch(Room::TWOVSTWO);
      else if (group->size == 3)
        job->quicklaunch(Room::THREEVSTHREE);
      else
        std::cout << "ERROR: (GIO::Controller::core_launch) can't choice game" << std::endl;
    }
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_launchSpeed3(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->launchSpeed3();
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->quicklaunch(Room::THREEVSTHREE);
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_launchSpeed2(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->launchSpeed2();
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->quicklaunch(Room::TWOVSTWO);
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_launchSpeed1(const std::string& act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->launchSpeed1();
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->quicklaunch(Room::ONEVSONE);
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_back(const std::string& act)
{
  bool trb = false;
  trb = true;
  core->back();
  core->setUser("");
  core->setType(GUI::Core::HOME);
  friends->setVisible(false);
  convers->setVisible(false);
  race->setVisible(false);
  group->setVisible(false);
  this->popup_close();
  popup->setVisible(false);
  // NETWORK

  // Protocol::Job *job = Factory::Protocol::Job::create();
  // job->quicklaunch(Room::ONEVSONE);
  // Network::Manager::Client::getInstance()->push(job);

  Application::getInstance()->reconnect();

  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::core_gameLoading(const std::string &act)
{
  bool trb = false;
  trb = true;
  this->popup_close();
  stack.push_back(GUI::Controller::POPUP);
  popup->setType(GUI::Popup::RESULT, "LET'S GO !!!");

  this->setVisible(false);
  this->launchGame = true;
  group_closeGroup("");
  Application::getInstance()->setViewport("GameScene");

  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::core_setting(const std::string &act)
{
  bool trb = false;
  if (can_access_core())
  {
    trb = true;
    core->setting();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::core_receiveStartGame(const std::string &act)
{
  bool trb = false;
  trb = true;
  core->startGame();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::core_receiveStopGame(const std::string &act)
{
  bool trb = false;
  trb = true;
  core->stopGame();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __CONVERS_HPP__

void  GUI::Controller::convers_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (convers_fct.find(prec) != convers_fct.end())
  {
    (this->*convers_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_convers()
{
  return (stack.back() != GUI::Controller::POPUP && stack.back() != GUI::Controller::SIGNINUP &&
          stack.back() != GUI::Controller::PROFILE && stack.back() != GUI::Controller::SETTING);
}

void  GUI::Controller::convers_closeBubble(const std::string& act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->closeBubble();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::convers_input(const std::string &act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    this->convers_sendMessage(act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::convers_sendMessage(const std::string& act)
{
  bool  trb = false;
  if (can_access_convers())
  {
    trb = true;
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->sendWhisp(convers->getUser(), convers->getInput());
    Network::Manager::Client::getInstance()->push(job);

    convers->sendMessage(convers->getUser(), convers->getInput());
   // convers->sendMessage(convers->getUser(), convers->getInput());
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::convers_receiveMessage(const std::string& pseudo, const std::string& from,
                                              const std::string& message)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    if (core->getUser() == from)
      convers->receiveMessage(pseudo, message, true);
    else
      convers->receiveMessage(from, message, false);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::convers_hiddenByPseudo(const std::string& act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->hiddenByPseudo("");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::convers_selectedBox(const std::string& act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->selectedBox(act, false);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::convers_moveUp(const std::string& act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->moveUp();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::convers_moveDown(const std::string& act)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->moveDown();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::convers_new(const std::string &name)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->selectedBox(name, true);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::convers_old(const std::string &name)
{
  bool trb = false;
  if (can_access_convers())
  {
    trb = true;
    convers->selectedBox(name, false);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __FRIENDS_HPP__

void  GUI::Controller::friends_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (friends_fct.find(prec) != friends_fct.end())
  {
    (this->*friends_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_friends()
{
  return (stack.back() != GUI::Controller::POPUP && stack.back() != GUI::Controller::SIGNINUP &&
          stack.back() != GUI::Controller::PROFILE && stack.back() != GUI::Controller::SETTING);
}

void GUI::Controller::friends_mess(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    convers->receiveMessage(act, "");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_ingame(const std::string &act)
{
  bool  trb = false;
  if (_MB_RIGHT)
  {
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->joinSpectator(act);
    Network::Manager::Client::getInstance()->push(job);
  }
  else if (can_access_friends())
  {
    trb = true;
    convers->receiveMessage(act, "");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::friends_infoFriend(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    friends->infoFriend("");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::friends_moveUp(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    friends->moveUp();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::friends_moveDown(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    friends->moveDown();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::friends_rmFriend(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    friends->rmFriend("");
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::INPUT, "Enter pseudo for delete :");
    popup->setAnswer("validate", "friends_sendDeleteFriend");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_sendDeleteFriend(const std::string &act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::RESULT, "Votre demande de suppresion a ete effectue");
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->removeFriend(popup->getInput());
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::friends_addFriend(const std::string& act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    friends->addFriend("");
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::INPUT, "Enter pseudo for add :");
    popup->setAnswer("validate", "friends_sendAddFriend");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_sendAddFriend(const std::string &act)
{
  bool trb = false;
  if (can_access_friends())
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::RESULT, "Votre demande d'amis a ete pris en compte");
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->friendRequest(popup->getInput());
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_receiveRequestFriend(const std::string &act)
{
  bool  trb = false;
  if (can_access_friends())
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::PROPOSITION, "[" + act + "] souhaites-vous inviter");
    popup->setAnswer("validate", "friends_answerRequestFriend_validate_" + act);
    popup->setAnswer("cancel", "friends_answerRequestFriend_cancel_" + act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_answerRequestFriend(const std::string &act)
{
  bool trb = false;
  std::string user = "";
  std::string cmd = "";
  int pos = act.find("_");

  if (pos > 0 && pos < act.size())
  {
    user = act.substr(pos + 1);
    cmd = act.substr(0, pos);
  }
  if (can_access_friends())
  {
    if (cmd == "validate")
    {
      // Accept la demande d'amis
      trb = true;
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->answerFriendRequest(user, true);
      Network::Manager::Client::getInstance()->push(job);
    }
    else if (cmd == "cancel")
    {
      // Refuse la demande d'amis
      trb = true;
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->answerFriendRequest(user, false);
      Network::Manager::Client::getInstance()->push(job);
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_receiveAddFriend(const std::string &act, User::Status stat)
{
  bool trb = true;
  std::map<User::Status, GUI::Activity::Player> convert;
  convert[User::CONNECTED] = GUI::Activity::ON;
  convert[User::DISCONNECTED] = GUI::Activity::OFF;
  convert[User::AFK] = GUI::Activity::AWAY;
  convert[User::BUSY] = GUI::Activity::IGAME;

  friends->infoFriend(act, convert[stat]);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_receiveDeleteFriend(const std::string &act)
{
  bool trb = true;

  friends->rmFriend(act);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::friends_receiveUpdateFriend(const std::string &act, User::Status stat)
{
  bool trb = true;
  std::map<User::Status, GUI::Activity::Player> convert;
  convert[User::CONNECTED] = GUI::Activity::ON;
  convert[User::DISCONNECTED] = GUI::Activity::OFF;
  convert[User::AFK] = GUI::Activity::AWAY;
  convert[User::BUSY] = GUI::Activity::IGAME;

  friends->infoFriend(act, convert[stat]);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __GROUP_HPP__

void  GUI::Controller::group_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (group_fct.find(prec) != group_fct.end())
  {
    (this->*group_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_group()
{
  return (stack.back() != GUI::Controller::POPUP && stack.back() != GUI::Controller::SIGNINUP &&
          stack.back() != GUI::Controller::PROFILE && stack.back() != GUI::Controller::SETTING);
}

void  GUI::Controller::group_receiveRequestGroup(const std::string &act)
{
  bool  trb = false;
  if (can_access_group())
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::PROPOSITION, "[" + act + "] vous invites dans une partie");
    popup->setAnswer("validate", "group_choiceAnswer_validate_" + act);
    popup->setAnswer("cancel", "group_choiceAnswer_cancel_" + act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_choiceAnswer(const std::string &act)
{
  bool  trb = false;
  std::string user = "";
  std::string cmd = "";
  int pos = act.find("_");

  std::cout << " :: "<< act << std::endl;
  if (pos > 0 && pos < act.size())
  {
    user = act.substr(pos + 1);
    cmd = act.substr(0, pos);
  }
  if (can_access_group())
  {
    if (cmd == "validate")
    {
      trb = true;
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->answerGroupRequest(user, true);
      Network::Manager::Client::getInstance()->push(job);
    }
    else if (cmd == "cancel")
    {
      trb = true;
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->answerGroupRequest(user, false);
      Network::Manager::Client::getInstance()->push(job);
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_addPlayerToGame(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    stack.push_back(GUI::Controller::POPUP);
    popup->setType(GUI::Popup::INPUT, "Enter pseudo for add :");
    popup->setAnswer("validate", "group_sendAddPlayerToGame");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_sendAddPlayerToGame(const std::string& act)
{
  bool trb = false;
  if (group->run)
  {
    trb = true;
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->addPlayerInGroup(popup->getInput());
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_addingPlayerToGame(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    group->addPlayerToGame("");
    // NETWORK
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_closeGroup(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    group->closeGroup();
    group->run = false;
    group->setVisible(false);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_removingPlayerToGame(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
    {
      trb = true;
      group->removePlayerToGame(act);
    }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_removePlayerToGame(const std::string& act)
{
  bool trb = false;
  if (core->run)
    {
      trb = true;
      if (act == core->getUser())
      {
        this->group_closeGroup(act);
        // NETWORK
        Protocol::Job *job = Factory::Protocol::Job::create();
        job->leaveGroup();
        Network::Manager::Client::getInstance()->push(job);
      }
      else
      {
        // NETWORK
        Protocol::Job *job = Factory::Protocol::Job::create();
        job->kickPlayerGroup(act);
        Network::Manager::Client::getInstance()->push(job);
      }
    }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_input(const std::string &act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    this->group_sendMessage(act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_sendMessage(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->sendMsgGroup(group->getInput());
    Network::Manager::Client::getInstance()->push(job);

    group->sendMessage("");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_receiveNewMemberGroup(const std::string &name, ::Race::Race r)
{
  bool trb = false;
  std::map< ::Race::Race, GUI::TYPE_RACE> convert_f_s;
  convert_f_s[::Race::RANDOM] = GUI::ALEA;
  convert_f_s[::Race::GENICIA] = GUI::R1;
  convert_f_s[::Race::HUMANOIDE] = GUI::R2;
  convert_f_s[::Race::IMPERIUM] = GUI::R3;
  if (group->run)
  {
    trb = true;
    group->playerJoin(name, convert_f_s[r]);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_receiveMessage(const std::string& pseudo, const std::string& message)
{
  bool trb = false;
  if (group->run)
  {
    trb = true;
    group->addMessage(pseudo, message, 0);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_receiveLeftPlayer(const std::string &act)
{
  bool trb = false;
  if (group->run)
  {
    trb = true;
    group->deleteUser(act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::group_receiveMemberChangedRace(const std::string &name, ::Race::Race r)
{
  bool trb = false;
  std::map<::Race::Race, GUI::TYPE_RACE> convert_f_s;
  convert_f_s[::Race::RANDOM] = GUI::ALEA;
  convert_f_s[::Race::GENICIA] = GUI::R1;
  convert_f_s[::Race::HUMANOIDE] = GUI::R2;
  convert_f_s[::Race::IMPERIUM] = GUI::R3;
  if (group->run)
  {
    trb = true;
    group->updateUser(name, convert_f_s[r]);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_updateUser(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    group->updateUser("", GUI::ALEA);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::group_deleteUser(const std::string& act)
{
  bool trb = false;
  if (can_access_group())
  {
    trb = true;
    group->deleteUser("");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __POPUP_HPP__

void  GUI::Controller::popup_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (popup_fct.find(prec) != popup_fct.end())
  {
    (this->*popup_fct[prec])(next);
  }
}

bool GUI::Controller::can_access_popup()
{
  return (stack.back() == GUI::Controller::POPUP);
}

void  GUI::Controller::popup_close()
{
  if (stack.back() == GUI::Controller::POPUP)
    stack.pop_back();
  popup->setVisible(false);
}

void GUI::Controller::popup_accept(const std::string &act)
{
  bool trb = false;
  if (can_access_popup())
  {
    trb = true;
    this->popup_close();
    this->click(popup->getAnswer("accept"));
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::popup_input(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    trb = true;
    this->popup_validate(act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::popup_cancel(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    trb = true;
    this->popup_close();
    this->click(popup->getAnswer("cancel"));
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::popup_validate(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    trb = true;
    this->popup_close();
    this->click(popup->getAnswer("validate"));
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::popup_exit(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    trb = true;
    this->popup_close();
    this->click(popup->getAnswer("exit"));
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __PROFILE_HPP__

void  GUI::Controller::profile_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (profile_fct.find(prec) != profile_fct.end())
  {
    (this->*profile_fct[prec])(prec);
  }
}

bool  GUI::Controller::can_access_profile()
{
  return (stack.back() == GUI::Controller::PROFILE);
}

void GUI::Controller::profile_updateMyUserData(const std::string& act)
{
  bool trb = false;
  if (can_access_profile())
  {
    trb = true;
    profile->updateMyUserData("", "");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::profile_updateUserData(const std::string& act)
{
  bool trb = false;
  if (can_access_profile())
  {
    trb = true;
    profile->updateUserData("", "");
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::profile_exit(const std::string& act)
{
  bool trb = false;
  if (can_access_profile())
  {
    trb = true;
    profile->exit();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __RACE_HPP__

void  GUI::Controller::race_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (race_fct.find(prec) != race_fct.end())
  {
    (this->*race_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_race()
{
  return (stack.back() != GUI::Controller::POPUP && stack.back() != GUI::Controller::SIGNINUP &&
          stack.back() != GUI::Controller::PROFILE && stack.back() != GUI::Controller::SETTING);
}

void GUI::Controller::race_setRace(const std::string& act)
{
  std::map<std::string, GUI::TYPE_RACE> convert_s_to_e;
  convert_s_to_e["alea"]  = GUI::ALEA;
  convert_s_to_e["r1"]    = GUI::R1;
  convert_s_to_e["r2"]    = GUI::R2;
  convert_s_to_e["r3"]    = GUI::R3;
  std::map<std::string, ::Race::Race> convert_f_s;
  convert_f_s["alea"] = ::Race::RANDOM;
  convert_f_s["r1"]   = ::Race::GENICIA;
  convert_f_s["r2"]   = ::Race::HUMANOIDE;
  convert_f_s["r3"]   = ::Race::IMPERIUM;

  bool trb = false;
  if (can_access_race())
  {
    if (convert_s_to_e.find(act) != convert_s_to_e.end())
    {
      trb = true;
      race->setType(convert_s_to_e[act]);
        // NETWORK
        Protocol::Job *job = Factory::Protocol::Job::create();
        job->setRace(convert_f_s[act]);
        Network::Manager::Client::getInstance()->push(job);
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __SETTING_HPP__

void  GUI::Controller::setting_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (setting_fct.find(prec) != setting_fct.end())
  {
    (this->*setting_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_setting()
{
  return (stack.back() == GUI::Controller::SETTING);
}

void  GUI::Controller::setting_exit(const std::string& act)
{
  bool trb = false;
  if (can_access_setting())
  {
    trb  = true;
    setting->exit();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

// __SIGNINUP_HPP__

void  GUI::Controller::signinup_function(const std::string& name)
{
  int pos = name.find("_");
  std::string prec = "";
  std::string next = "";
  if (pos > 0 && pos < name.size())
  {
    prec = name.substr(0, pos);
    next = name.substr(pos + 1);
  }
  else
    prec = name;
  if (signinup_fct.find(prec) != signinup_fct.end())
  {
    (this->*signinup_fct[prec])(next);
  }
}

bool  GUI::Controller::can_access_signinup()
{
  return (stack.back() == GUI::Controller::SIGNINUP);
}

void  GUI::Controller::signinup_input(const std::string& act)
{
  bool trb = false;
  if (can_access_signinup())
  {
    trb = true;
    this->signinup_validate(act);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::signinup_validate(const std::string& act)
{
  bool trb = false;
  if (can_access_signinup())
  {
    if (sign->getType() == GUI::SignInUp::SIGNUP)
    {
      trb = true;
      sign->validate("", "");
      stack.push_back(GUI::Controller::POPUP);
      popup->setType(GUI::Popup::RESULT, "Form sent, wait...");
      // NETWORK
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->registration(sign->getPseudo(), sign->getMail(), Algo::MD5::getInstance()->digest(sign->getPassword()));
      Network::Manager::Client::getInstance()->push(job);
    }
    else
    {
      trb = true;
      sign->validate("", "");
      stack.push_back(GUI::Controller::POPUP);
      popup->setType(GUI::Popup::RESULT, "Authentification waiting...");
      // NETWORK
      Protocol::Job *job = Factory::Protocol::Job::create();
      job->connection(sign->getPseudo(), Algo::MD5::getInstance()->digest(sign->getPassword()));
      Network::Manager::Client::getInstance()->push(job);
    }
  /*  core->setType(GUI::Core::ONLINE);// A METTRE DANS UNE AUTRE FONCTION UNIQUEMENT POUR DEBUGUER....
    friends->setVisible(true);
    convers->setVisible(true);
    this->signinup_exit("");*/
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::signinup_signIn(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
    this->popup_close();
  if (can_access_signinup())
  {
    trb = true;
    sign->signIn();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::signinup_UPsuccessfull(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    this->popup_close();
    if (can_access_signinup())
    {
      trb = true;
      stack.push_back(GUI::Controller::POPUP);
      popup->setType(GUI::Popup::RESULT, "Subscribtion Successfull ! You can now log in");
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::signinup_UPerror(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    this->popup_close();
    if (can_access_signinup())
    {
      trb = true;
      stack.push_back(GUI::Controller::POPUP);
      popup->setType(GUI::Popup::RESULT, "Subscription Error");
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::signinup_INsuccessfull(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    this->popup_close();
    if (can_access_signinup())
    {
      trb = true;
      core->setUser(sign->getPseudo());
      core->setType(GUI::Core::ONLINE);// A METTRE DANS UNE AUTRE FONCTION UNIQUEMENT POUR DEBUGUER....
      friends->setVisible(true);
      convers->setVisible(true);
      race->setVisible(true);
      this->signinup_exit("");
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUI::Controller::signinup_INerror(const std::string& act)
{
  bool trb = false;
  if (can_access_popup())
  {
    this->popup_close();
    if (can_access_signinup())
    {
      trb = true;
      stack.push_back(GUI::Controller::POPUP);
      popup->setType(GUI::Popup::RESULT, "Connection Error");
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::signinup_signUp(const std::string& act)
{
  bool trb = false;
  if (can_access_signinup())
  {
    trb = true;
    sign->signUp();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void GUI::Controller::signinup_exit(const std::string& act)
{
  bool trb = false;
  if (can_access_signinup())
  {
    trb = true;
    sign->exit();
    stack.pop_back();
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}
