// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  <unistd.h>
#include  <sys/types.h>
#include <math.h>
#include  "GUIG/Controller.hpp"
#include	"Utils/convert.hpp"
#include	"Logger.hpp"
#include "Kernel/Manager.hpp"

#ifndef DEBUG_CONTROLLER
  # include  <iostream>
  static void  function_debug(const std::string& file, const std::string& fct, int line, bool access)
  {
    std::cout << "\033[35m" << file << "\033[0m " <<  line << "\t- " << fct;
    if (!access)
      std::cout << "\033[31m : Access denied \033[0m";
    std::cout << std::endl;
  }
  # define  __CALL_FUNCTION_DEBUG__(file, fct, line, trb) function_debug(file, fct, line, trb)
#else
  # define  __CALL_FUNCTION_DEBUG__(file, fct, line, trb)
#endif


GUIG::Controller::Controller(Ogre::RenderWindow *win) :
        AScene(std::string("GameScene"), win, Ogre::ColourValue(0.08,0.08,0.08)),
        _soleil(NULL), inGame(false), _KC_UP(false), _KC_DOWN(false), _KC_LEFT(false), _KC_RIGHT(false), _KC_CTRL(false),
        parserRace(), mousePosition(0.0f, 0.0f), _mousePressed(0.0f, 0.0f), _mouseReleased(0.0f, 0.0f),
        minimap(NULL), ressource(NULL), progress(NULL),
        _player(NULL), _MB_LEFT(false), _MB_RIGHT(false), _actClick(false), _mapIsInit(false),
        _actClickAction(GUIG::Controller::UNKNOWN), _actClickActionBis(GUIG::Controller::UNKNOWN),
        _serialAction(""), _idPlayerTMP(0)
{
  bool trb = false;
  trb = true;

  CONTROLLER_FCT["controllerEmpty"]       = &GUIG::Controller::controllerEmpty;

  CONTROLLER_FCT["progress"]    = &GUIG::Controller::progress_function;
  // progress_fct = &GUIG::Controller::progress_--------;

  CONTROLLER_FCT["minimap"]     = &GUIG::Controller::minimap_function;
  minimap_fct["moveLook"]       = &GUIG::Controller::minimap_moveLook;
  // minimap_fct = &GUI::Controller::minimap_--------;

  CONTROLLER_FCT["ressource"]   = &GUIG::Controller::ressource_function;
  // ressource_fct = &GUIG::Controller::ressource_--------;

  CONTROLLER_FCT["guigProfile"] = &GUIG::Controller::guigProfile_function;
  // guigProfile_fct = &GUIG::Controller::guigProfile_-----;
  guigProfile_fct["capacities"] = &GUIG::Controller::guigProfile_capacities;
  guigProfile_fct["objects"]    = &GUIG::Controller::guigProfile_objects;
  guigProfile_fct["effects"]    = &GUIG::Controller::guigProfile_effects;
  guigProfile_fct["production"] = &GUIG::Controller::guigProfile_productions;

  CONTROLLER_FCT["guigSquad"]   = &GUIG::Controller::guigSquad_function;
  guigSquad_fct["round"]        = &GUIG::Controller::guigSquad_round;
  guigSquad_fct["shield"]       = &GUIG::Controller::guigSquad_shield;
  guigSquad_fct["attack"]       = &GUIG::Controller::guigSquad_attack;
  guigSquad_fct["alert"]        = &GUIG::Controller::guigSquad_alert;
  guigSquad_fct["cancel"]       = &GUIG::Controller::guigSquad_cancel;
  // guigSquad_fct = &GUIG::Controller::guigSquad_------;

  CONTROLLER_FCT["element3D"]   = &GUIG::Controller::element3D_function;
  // element3D_fct = &GUIG::Controller::element3D__------;

  CONTROLLER_FCT["guigChatbox"]   = &GUIG::Controller::guigChatbox_function;
  guigChatbox_fct["input"]            = &GUIG::Controller::guigChatbox_input;
  // guigChatbox_fct = &GUIG::Controller::guigChatbox_-----; 
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

GUIG::Controller::~Controller()
{
  bool trb = false;
  trb = true;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

bool  GUIG::Controller::keyPressed(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
    controller_menuSwitch();
  else if (e.key == OIS::KC_TAB)
    controller_menuallyActivate();
  else if (e.key == OIS::KC_F3)
    Application::getInstance()->setViewport("MenuScene");
  else if (e.key == OIS::KC_F1)
    this->startLoading();
  else if (e.key == OIS::KC_F12)
    Application::getInstance()->exit();
  else if (e.key == OIS::KC_UP)
    _KC_UP = true;
  else if (e.key == OIS::KC_DOWN)
    _KC_DOWN = true;
  else if (e.key == OIS::KC_LEFT)
    _KC_LEFT = true;
  else if (e.key == OIS::KC_RIGHT)
    _KC_RIGHT = true;
  else if (e.key == OIS::KC_RCONTROL || e.key == OIS::KC_LCONTROL)
    _KC_CTRL = true;
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

bool  GUIG::Controller::keyReleased(const OIS::KeyEvent &e)
{
  if (_currentInput && !_currentInput->keyReleased(e))
    _currentInput = NULL;
  if (e.key == OIS::KC_UP)
    _KC_UP = false;
  else if (e.key == OIS::KC_DOWN)
    _KC_DOWN = false;
  else if (e.key == OIS::KC_LEFT)
    _KC_LEFT = false;
  else if (e.key == OIS::KC_RIGHT)
    _KC_RIGHT = false;
  else if (e.key == OIS::KC_TAB)
    controller_menuallyDesactivate();
  else if (e.key == OIS::KC_RCONTROL || e.key == OIS::KC_LCONTROL)
    _KC_CTRL = false;
  else if (_KC_CTRL && (e.key == OIS::KC_1 || e.key == OIS::KC_2 || e.key == OIS::KC_3 || e.key == OIS::KC_4 ||
                        e.key == OIS::KC_5 || e.key == OIS::KC_6 || e.key == OIS::KC_7 || e.key == OIS::KC_8 ||
                        e.key == OIS::KC_9))
    tryToSavGroupUnit(e.key);
  else if (e.key == OIS::KC_1 || e.key == OIS::KC_2 || e.key == OIS::KC_3 || e.key == OIS::KC_4 ||
            e.key == OIS::KC_5 || e.key == OIS::KC_6 || e.key == OIS::KC_7 || e.key == OIS::KC_8 ||
            e.key == OIS::KC_9)
    tryToSelectGroupUnit(e.key);
  return true;
}

bool  GUIG::Controller::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  std::cout << "\t ---------MOUSE:PRESSED:BEGIN-----------" << std::endl;
  if (_currentInput)
  {
    _currentInput->unfocus();
    _currentInput = NULL;
  }

  mousePosition.x = Ogre::Real(e.state.X.abs);
  mousePosition.y = Ogre::Real(e.state.Y.abs);
  _mousePressed.x  = Ogre::Real(e.state.X.abs);
  _mousePressed.y  = Ogre::Real(e.state.Y.abs);
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
  std::cout << "\t ---------MOUSE:PRESSED:END-----------" << std::endl;
  return true;
}

bool  GUIG::Controller::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  bool  act = false;
  std::cout << "\t ---------MOUSE:RELEASED:BEGIN-----------" << std::endl;
  std::cout << "_ACTCLICKMODIFIED ::" << _actClickModified << " ; SERIAL ACTION :" << _serialAction << std::endl;
  std::cout << "_ACTCLICKMODIFIED ::" << _actClickModified << " ; SERIAL ACTION :" << _serialAction << std::endl;
  pickFirstObject3DOnClick(e);
  mousePosition.x = Ogre::Real(e.state.X.abs);
  mousePosition.y = Ogre::Real(e.state.Y.abs);
  _mouseReleased.x = Ogre::Real(e.state.X.abs);
  _mouseReleased.y = Ogre::Real(e.state.Y.abs);
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
              if (itr->isInside(e.state.X.abs, e.state.Y.abs))
              {
                std::cout << "X:" << e.state.X.abs << "  Y:" << e.state.Y.abs << std::endl;
                act = true;
                this->click(itr->getName());
              }
          }
        }
     }
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
  if (id == OIS::MB_Left && !act)
  {
    if (_objectClick)
    {
      std::string name = _objectClick->getName();
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
      if (_serialAction != "" || _actClick)
      {
        this->actionClickSpecial(next);
      }
      else
      {
        this->click(next);
      }
    }
    else
    {
      guigProfile_unFocus();
    }
  }
  else if (id == OIS::MB_Right && !act)
  {
    if (_objectClick)
    {
      std::string name = _objectClick->getName();
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
      this->actionClick(next);
    }
  }
  else
  {
  }
  if (!act && !_actClickModified)
  {
    _actClickAction = GUIG::Controller::UNKNOWN;
    _serialAction = "";
  }
  _actClickModified = false;
  std::cout << "\t ---------MOUSE:RELEASED:END-----------" << std::endl;
  return true;
}

bool  GUIG::Controller::mouseMoved(const OIS::MouseEvent &e)
{
  std::cout << "\t ---------MOUSE:MOVED:BEGIN-----------" << std::endl;
  mousePosition.x = Ogre::Real(e.state.X.abs);
  mousePosition.y = Ogre::Real(e.state.Y.abs);
   for(std::map<std::string, AOverlaySceneManager*>::iterator it = _overlayManagerMap.begin();
       it != _overlayManagerMap.end(); ++it)
    {
      if (it->second)
      {
        std::vector<AOverlay *> ptr = (it->second)->getOverlayAt(e.state.X.abs, e.state.Y.abs);
        if (ptr.size() > 0)
        {
        }
        if (ptr.size() > 1)
        {
        }
        if (ptr.size() != 1 && _currentOn)
        {
          _currentOn->reinitZOrder();
          _currentOn = NULL;
        }
        if (ptr.size() == 1)
        {
          if (_currentOn && _currentOn != ptr.front())
            _currentOn->reinitZOrder();
          else if (!ptr.front()->isLocked())
          {
            _currentOn = ptr.front();
            _currentOn->changeZOrder(2);
          }
          break;
        }
      }
      else
      {
      }
    };
    checkIfCapacity(_currentOn);
    std::cout << "\t ---------MOUSE:MOVED:END-----------" << std::endl;
    return (AScene::mouseMoved(e));
}

void  GUIG::Controller::checkIfCapacity(AOverlay *ptr)
{
  if (!ptr)
  {
    _savTMPhover = NULL;
    annotationbis->setVisible(false);
  }
  else if (!_savTMPhover && _player && ptr != _savTMPhover)
  {
    _savTMPhover = ptr;
    std::string name = ptr->getName();
    int pos = name.find("_");
    std::string prec = "";
    std::string next = "";
    if (pos > 0 && pos < name.size())
    {
      prec = name.substr(0, pos);
      next = name.substr(pos + 1);
    }
    else
    {
      checkIfCapacity(NULL);
    }

    int pos2 = next.find("_");
    std::string type = "";
    std::string next2 = "";
    if (pos2 > 0 && pos2 < next.size())
    {
      type = next.substr(0, pos2);
      next2 = next.substr(pos2 + 1);
    }
    else
    {
      checkIfCapacity(NULL);
    }

    int pos3 = next2.find("_");
    std::string serial  = "";
    std::string osef    = "";
    if (pos3 > 0 && pos3 < next2.size())
    {
      serial = next2.substr(0, pos3);
      annotationbis->setVisible(true);
      annotationbis->update(serial, _player);
    }
    else
    {
      checkIfCapacity(NULL);
    }
  }
}

bool  GUIG::Controller::updateFrame(const Ogre::FrameEvent &evt)
{
  bool  ret = true;

  for (auto it : _listMove)
    ret = ((it)->update(evt) == false ? false : ret);
  clearListMove();
  Protocol::Job *job = NULL;
  while ((job = Network::Manager::Client::getInstance()->getJob()))
  {
    Client::JobController::getInstance()->doJobGame(job, this);
  }
  if (inGame)
  {
    if (_KC_UP)
      this->moveCameraUp();
    if (_KC_DOWN)
      this->moveCameraDown();
    if (_KC_LEFT)
      this->moveCameraLeft();
    if (_KC_RIGHT)
      this->moveCameraRight();

    if (mousePosition.x < 2)
      this->moveCameraLeft();
    else if (mousePosition.x > _window->getWidth() - 2)
      this->moveCameraRight();

    if (mousePosition.y < 2)
      this->moveCameraUp();
    else if (mousePosition.y > _window->getHeight() - 2)
      this->moveCameraDown();
  }
  if (_elements.find(_UnitSelectedId) != _elements.end() && _elements[_UnitSelectedId] != NULL && _UnitSelectedId != 0)
    annotation->update(this->_elements[_UnitSelectedId]);
  game_itemReplace();
  squad->update(_elements);
  return (true);
}

//		BIND DES BUTTONS

void    GUIG::Controller::tryToSavGroupUnit(OIS::KeyCode key)
{
  if (quickSav.find(key) != quickSav.end())
    quickSav[key].clear();
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  for (std::vector<Kernel::ID::id_t>::const_iterator it = ids.begin(); it != ids.end(); ++it)
  {
    quickSav[key].push_back(*it);
  }
}

void    GUIG::Controller::tryToSelectGroupUnit(OIS::KeyCode key)
{
  guigProfile_clean();
  if (quickSav.find(key) != quickSav.end())
  {
    std::vector<std::vector<Kernel::ID::id_t>::iterator> iteratorList;
    bool  first = true;
    for (std::vector<Kernel::ID::id_t>::iterator it = quickSav[key].begin(); it != quickSav[key].end(); ++it)
    {
      if (_elements.find(*it) != _elements.end() && _elements[*it])
      {
        const Kernel::Data  *ptr = Kernel::Manager::getInstance()->getData(_elements[*it]->serial());

        squad->addUnit(ptr->icon, *it, _elements[*it]->serial());
        if (first)
        {
          _UnitIsSelected = true;
          guigProfile_putIcon(*it);
          guigProfile_putCapacities(*it);
          guigProfile_putObjects(*it);
          guigProfile_putProductions(*it);
          guigProfile_putEffects(*it);

          annotation->update(_elements[*it]);
          annotation->setVisible(true);
        }
        first = false;
      }
      else
        iteratorList.push_back(it);
    }
    for (std::vector<std::vector<Kernel::ID::id_t>::iterator>::iterator it = iteratorList.begin();
          it != iteratorList.end(); ++it)
    {
      quickSav[key].erase(*it);
    }
  }
  profile->draw();
}

static bool	zoomPlusMinimap(AScene *scene, AOverlay *overlay)
{
  if (GUIG::Controller *ptr = dynamic_cast<GUIG::Controller *>(scene))
    ptr->zoomMinimap(1);
  return true;
}

static bool	zoomMinusMinimap(AScene *scene, AOverlay *overlay)
{
  if (GUIG::Controller *ptr = dynamic_cast<GUIG::Controller *>(scene))
    ptr->zoomMinimap(-1);
  return true;
}

void  GUIG::Controller::createScene()
{
  _sceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.8));

  progress = new GUIG::Progress();
  _overlayManagerMap["progress"] = progress;
  _overlayManagerMap["progress"]->init(_window->getWidth(), _window->getHeight());

  Ogre::Vector2		minimapSize(250,250);

  minimap = new GUIG::Minimap(30, minimapSize);
  _overlayManagerMap["minimap"] = minimap;
  _overlayManagerMap["minimap"]->init(_window->getWidth(), _window->getHeight());
  minimap->setRelatifPosition(50, _window->getHeight() - (50 + minimapSize.y));
  minimap->draw();

  ressource = new GUIG::Ressource();
  _overlayManagerMap["ressource"] = ressource;
  ressource->setRelatifPosition(70, 15);
  _overlayManagerMap["ressource"]->init(_window->getWidth(), _window->getHeight());

  annotation = new GUIG::Annotation();
  _overlayManagerMap["annotation"] = annotation;
  annotation->setRelatifPosition(1600, 20);
  _overlayManagerMap["annotation"]->init(_window->getWidth(), _window->getHeight());
  annotation->draw();

  daynight = new GUIG::DayNight();
  _overlayManagerMap["daynight"] = daynight;
  daynight->setRelatifPosition(775, 20);
  _overlayManagerMap["daynight"]->init(_window->getWidth(), _window->getHeight());

  annotationbis = new GUIG::AnnotationBis();
  annotationbis->setRelatifPosition(1600, 400);
  _overlayManagerMap["annotationbis"] = annotationbis;
  _overlayManagerMap["annotationbis"]->init(_window->getWidth(), _window->getHeight());
  annotationbis->draw();

  allymenu = new GUIG::AllyMenu();
  allymenu->setRelatifPosition(710, 300);
  _overlayManagerMap["allymenu"] = allymenu;
  _overlayManagerMap["allymenu"]->init(_window->getWidth(), _window->getHeight());
  allymenu->draw();

  profile = new GUIG::Profile();
  profile->setRelatifPosition(700,800);
  _overlayManagerMap["guigProfile"] = profile;
  _overlayManagerMap["guigProfile"]->init(_window->getWidth(), _window->getHeight());
  profile->draw();

  menu = new GUIG::Menu();
  menu->setRelatifPosition(0, 0);
  _overlayManagerMap["menu"] = menu;
  _overlayManagerMap["menu"]->init(_window->getWidth(), _window->getHeight());
  menu->draw();

  squad = new GUIG::Squad();
  squad->setRelatifPosition(1440, 840);
  _overlayManagerMap["squad"] = squad;
  _overlayManagerMap["squad"]->init(_window->getWidth(), _window->getHeight());
  squad->draw();

  chatbox = new GUIG::ChatBox();
  chatbox->setRelatifPosition(20, 300);
  _overlayManagerMap["chatbox"] = chatbox;
  _overlayManagerMap["chatbox"]->init(_window->getWidth(), _window->getHeight());
  chatbox->draw();

  // Bin des buttons sur les bonnes fonctions
  subscribe(minimap->getPlusButton(), &zoomPlusMinimap);
  subscribe(minimap->getMinusButton(), &zoomMinusMinimap);

  // Visibility
  startLoading();

  _currentInput = NULL;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::drawInterface()
{
  progress->setVisible(!inGame);
  minimap->setVisible(inGame);
  ressource->setVisible(inGame);
  annotation->setVisible(false);
  profile->setVisible(inGame);
  squad->setVisible(inGame);
  daynight->setVisible(inGame);
  annotationbis->setVisible(false);
  allymenu->setVisible(false);
  menu->setVisible(false);
  chatbox->setVisible(inGame);
}

void  GUIG::Controller::controller_menuActivate(const std::string &)
{
  menu->setVisible(true);
}

void  GUIG::Controller::controller_menuDesactivate(const std::string &)
{
  menu->setVisible(false);
}

void  GUIG::Controller::controller_menuallyActivate(const std::string &)
{
  allymenu->setVisible(true);
}

void  GUIG::Controller::controller_menuallyDesactivate(const std::string &)
{
  allymenu->setVisible(false);
}

void  GUIG::Controller::controller_menuSwitch(const std::string &)
{
  menu->setVisible(!menu->isVisible());
}

void  GUIG::Controller::startLoading()
{
  inGame = false;
  drawInterface();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::endLoading()
{
  inGame = true;
  chatbox->enterGame();
  drawInterface();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::exitGame()
{
  inGame = false;
  chatbox->leaveGame();
  drawInterface();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}


// GAME

void  GUIG::Controller::game_itemReplace()
{
  if (_player && _soleil)
    _soleil->setVisible(false);
  else if (_soleil)
    _soleil->setVisible(true);
  for (std::map<Kernel::ID::id_t, Game::AElement*>::iterator it = _elements.begin(); it != _elements.end();
       ++it)
    {
      if (_elements3D.find(it->first) != _elements3D.end() && _elements3D[it->first] != NULL)
	{
	  if (this->_map->isVisible(_player, it->second))
	    {
	      double x = (it->second)->getX() * GUIG_SIZE_MAP_X;
	      double y = (it->second)->getZ() * 15.0;
	      double z = (it->second)->getY() * GUIG_SIZE_MAP_Y;
	      int o = (it->second)->getOrientation();

	      _elements3D[it->first]->setVisible();
        if (_elements[it->first]->getType() != Game::RESSSPOT)
	        _elements3D[it->first]->setPosition(x, y, z);
        else
        {
         if (dynamic_cast<Game::RessourcesSpot*>(_elements[it->first])->getSpotType() == Game::Ressources::GOLD)
	        _elements3D[it->first]->setPosition(x, y, z);
         else
	        _elements3D[it->first]->setPosition(x, y + 2.0f, z);
        }
	      if (_player && _elements[it->first]->getTeam() == _player->getTeam() && !_elements3D[it->first]->getLight())
		{
		  Ogre::Light *light = _sceneMgr->createLight("light_" + _elements[it->first]->serial() + "_" + toString(it->first));
		  light->setType(Ogre::Light::LT_POINT);
		  light->setAttenuation(30, 1, 0.008, 0);
		  _elements3D[it->first]->setLight(light);
		}
	      Ogre::Light *lt = _elements3D[it->first]->getLight();
	      if (lt)
		{
		  if (!daynight->isDay())
		    lt->setAttenuation(30, 1, 0.008, 0);
		  else
		    lt->setAttenuation(40, 1, 0.008, 0);
		  lt->setPosition(x, y + 25, z);
		}
	    }
	  else
	    {
	      _elements3D[it->first]->setVisible(false);
	    }
	}
      else
	std::cout << "C'est bizarrement null item: " << it->first << "["<< (_elements3D.find(it->first) != _elements3D.end()) <<"][" << (_elements3D[it->first] != NULL) << "] F(" << __FILE__  << ") l." << __LINE__ << std::endl;
    }
}

void  GUIG::Controller::game_itemDestruction(Kernel::ID::id_t id)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (_elements.find(id) == _elements.end())
    return;
  if (_elements[id] == NULL)
    {
      _elements.erase(_elements.find(id));
      return;
    }

  Game::Type type = _elements[id]->getType();
  if (Game::UNIT == type)
    {
      Factory::Game::Unit::remove(dynamic_cast<::Game::Unit*>(_elements[id]));
    }
  else if (Game::BUILDING == type)
    {
      Factory::Game::Building::remove(dynamic_cast<::Game::Building*>(_elements[id]));
    }
  else if (Game::HERO == type)
    {
      Factory::Game::Hero::remove(dynamic_cast<::Game::Hero*>(_elements[id]));
    }
  else if (Game::PROJECTILE == type)
    {
      Factory::Game::Projectile::remove(dynamic_cast<::Game::Projectile*>(_elements[id]));
    }
  else {
    return ;
  }
  this->_map->remove(_elements[id]);
  _elements[id] = NULL;
  _elements.erase(_elements.find(id));
  elementPoolManager.deleteElement(_elements3D[id]);
  _elements3D.erase(id);
}

Game::Player  *GUIG::Controller::game_findPlayer(Kernel::ID::id_t id)
{
  return _players[id];
}

void  GUIG::Controller::game_itemCreation(const Kernel::Serial & serial, Kernel::ID::id_t id,
                                          double x, double y, double z, int orientation, Kernel::ID::id_t ownerID)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!game_findPlayer(ownerID))
  {
    return;
  }
  Game::Type type = Kernel::Manager::getInstance()->getData(serial)->type;
  if (Game::UNIT == type)
  {
    _elements[id] = (Factory::Game::Unit::create(id, serial, game_findPlayer(ownerID), orientation, x, y, z));
  }
  else if (Game::BUILDING == type)
  {
    _elements[id] = (Factory::Game::Building::create(id, serial, game_findPlayer(ownerID), orientation, x, y, z));
  }
  else if (Game::HERO == type)
  {
    _elements[id] = (Factory::Game::Hero::create(id, serial, game_findPlayer(ownerID), orientation, x, y, z));
  }
  else if (Game::PROJECTILE == type)
  {
    _elements[id] = (Factory::Game::Projectile::create(id, serial, game_findPlayer(ownerID), orientation, x, y, z));
  }
  else {
    return ;
  }
  _elements3D[id] = elementPoolManager.getElement(serial);
  _elements3D[id]->getNode()->setScale(0.2, 0.2, 0.2);
  if (_player && _elements[id]->getTeam() == _player->getTeam())
  {
    Ogre::Light *light = _sceneMgr->createLight("light_" + serial + "_" + toString(id));
    light->setType(Ogre::Light::LT_POINT);
    light->setAttenuation(30, 1, 0.008, 0);
    std::cout << "ok" << std::endl;
    _elements3D[id]->setLight(light);
  }
  this->_map->push(_elements[id]);
}

void  GUIG::Controller::game_itemUpdate(Kernel::ID::id_t id,
                                        double x, double y, double z,
                                        int orientation,
                                        unsigned int life, unsigned int ress,
                                        unsigned int xp, unsigned int level)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  Game::Type type = _elements[id]->getType();

  if (dynamic_cast<Game::Movable *>(_elements[id]))
  {
    this->_map->remove(_elements[id]);
    (dynamic_cast<Game::Movable*>(_elements[id]))->setPosition(x, y, z);
    (dynamic_cast<Game::Movable*>(_elements[id]))->setOrientation(orientation);
    this->_map->push(_elements[id]);
  }
  _elements[id]->setLife(life);
  _elements[id]->setRessources(ress);
  if (dynamic_cast<Game::Unit*>(_elements[id]))
  {
    (dynamic_cast<Game::Unit*>(_elements[id]))->setXPLevel(xp, level);
  }
  _elements3D[id]->setOrientation(orientation);
}

void  GUIG::Controller::game_updateSpot(Kernel::ID::id_t id, unsigned int amount) {
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::RessourcesSpot *spot = dynamic_cast<Game::RessourcesSpot *>(this->_elements[id]);
  if (spot == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  spot->setAmount(amount);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::game_createSpot(Kernel::ID::id_t id, double x, double y, double z,
					  Game::Ressources::Type ress, unsigned int amount) {
  Game::RessourcesSpot *spot = Factory::Game::RessourcesSpot::create(id, x, y, z, ress, amount);
  this->_elements[id] = spot;
  this->_elements3D[id] = elementPoolManager.getElement(spot->serial());
  if (_elements[id]->getInfos().data->model == "goldmine.mesh") {
    this->_elements3D[id]->getNode()->setScale(5.0, 5.0, 5.0);
  }
  else {
    this->_elements3D[id]->getNode()->setScale(2.0, 2.0, 2.0);
    Ogre::SceneNode *s = this->_elements3D[id]->getNode();
    Ogre::Vector3 v = s->getPosition();
    v.z += 20.0;
    s->setPosition(v);
  }
  this->_map->push(spot);
 __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_setRessource(Kernel::ID::id_t id,
                                          unsigned int gold, unsigned int wood, unsigned int food)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (_players[id]) {
    _players[id]->setRessources(Game::Ressources::GOLD, gold);
    _players[id]->setRessources(Game::Ressources::WOOD, wood);
    _players[id]->setRessources(Game::Ressources::FOOD, food);
    if (_player && id == _player->getID()) {
      ressource->setGold(gold);
      ressource->setWood(wood);
      ressource->setFood(food);
    }
  }
}

bool  GUIG::Controller::itemExist(Kernel::ID::id_t id)
{
  if (_elements.find(id) == _elements.end() || !_elements[id])
    return (false);
  return (true);
}

void  GUIG::Controller::game_effectNotApplyOnItem(Kernel::ID::id_t id, const Kernel::Serial & effect)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  _elements[id]->removeEffect(effect);
}

void  GUIG::Controller::game_objectKeepedByHero(Kernel::ID::id_t id, Kernel::ID::id_t obj)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id) || !itemExist(obj))
    return;
  if (dynamic_cast<::Game::Hero*>(_elements[id]) &&
      dynamic_cast<::Game::Object*>(_elements[obj]))
  {
    (dynamic_cast<::Game::Hero*>(_elements[id]))->addObject(dynamic_cast<::Game::Object*>(_elements[obj]));
  }
}

void  GUIG::Controller::game_objectPutByHero(Kernel::ID::id_t id, Kernel::ID::id_t obj)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id) || !itemExist(obj))
    return;
  if (dynamic_cast<::Game::Hero*>(_elements[id]) &&
      dynamic_cast<::Game::Object*>(_elements[obj]))
  {
    (dynamic_cast<::Game::Hero*>(_elements[id]))->removeObject(dynamic_cast<::Game::Object*>(_elements[obj]));
  }
}

void  GUIG::Controller::game_objectPossessedByHero(Kernel::ID::id_t id, const std::vector<Kernel::ID::id_t> &objs)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return;
  }
  Game::Hero *hero = dynamic_cast<Game::Hero *>(this->_elements[id]);
  if (hero == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  std::list<Game::Object *> list = hero->getObjects();
  for (auto it : hero->getObjects()) {
    if (std::find(objs.begin(), objs.end(), it->getID()) == objs.end()) {
      hero->removeObject(it);
    }
  }
  list = hero->getObjects();
  for (auto it : objs) {
    bool in = false;
    for (auto it2 : list) {
      if (it2->getID() == it) {
	in = true;
	break;
      }
    }
    if (!in) {
      if (itemExist(it) && dynamic_cast<Game::Object *>(this->_elements[it])) {
	hero->addObject(dynamic_cast<Game::Object *>(this->_elements[it]));
      }
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_waypointOfItem(Kernel::ID::id_t id, double x, double y , double z, double speed, unsigned int)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  Game::Movable *item = dynamic_cast<Game::Movable *>(this->_elements[id]);
  if (item) {
    item->setWaypoints(std::vector<Vector3d>(1, Vector3d(x, y, z)));
    this->_elements[id]->setSpeed(speed);
  }
}

void  GUIG::Controller::game_itemMoving(Kernel::ID::id_t id, double x, double y, double z)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  Game::Action *action = Factory::Game::Action::create(Game::ACTION_MOVE);
  action->move.x = x;
  action->move.y = y;
  action->move.z = z;
  _elements[id]->setAction(action);
}

void  GUIG::Controller::game_stopingAction(Kernel::ID::id_t id)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  _elements[id]->stopAction();
}

void  GUIG::Controller::game_itemAction(Kernel::ID::id_t id, Game::eAction act)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  Game::Action *action = Factory::Game::Action::create(act);
  _elements[id]->setAction(action);
}

void  GUIG::Controller::game_effectNoApplyOnItem(Kernel::ID::id_t id, const Kernel::Serial &effect)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  if (!itemExist(id))
    return;
  _elements[id]->removeEffect(effect);
}

void  GUIG::Controller::game_externEffectApplyOnItem(Kernel::ID::id_t id, Kernel::ID::id_t idEffectOwner,
                                                      const Kernel::Serial &serial)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(idEffectOwner)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::AElement *from = this->_elements[idEffectOwner];
  Game::AElement *to = this->_elements[id];
  const Game::Effect *effect = NULL;
  const Game::AElement::EffectContainer frEffects = from->getEffects();
  if (frEffects.find(serial) == frEffects.end()) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  const std::list<const Game::Effect *> toEffects = to->getTemporaryEffects();
  for (auto it : frEffects.at(serial)) {
    if (std::find(toEffects.begin(), toEffects.end(), it) == toEffects.end()) {
      to->addEffect(it);
      __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
      return ;
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
}

void  GUIG::Controller::game_externEffectNotApplyOnItem(Kernel::ID::id_t id, Kernel::ID::id_t idEffectOwner,
							const Kernel::Serial &serial)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(idEffectOwner)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::AElement *from = this->_elements[idEffectOwner];
  Game::AElement *to = this->_elements[id];
  const Game::AElement::EffectContainer frEffects = from->getEffects();
  if (frEffects.find(serial) == frEffects.end()) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (frEffects.at(serial).empty()) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  const std::list<const Game::Effect *> toEffects = to->getTemporaryEffects();
  if (std::find(toEffects.begin(), toEffects.end(), frEffects.at(serial).front()) != toEffects.end()) {
    to->removeEffect(frEffects.at(serial).front());
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  }
  else {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
  }
}

void  GUIG::Controller::game_effectApplyOnItem(Kernel::ID::id_t id, const Kernel::Serial &serial, double)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  this->_elements[id]->addEffect(serial);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_stanceOfUnit(Kernel::ID::id_t id, Game::Stance::Type stance)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (dynamic_cast<Game::Unit *>(this->_elements[id])) {
    dynamic_cast<Game::Unit *>(this->_elements[id])->setStance(stance);
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  }
  else {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
  }
}

void  GUIG::Controller::game_unitHasBeenProduct(Kernel::ID::id_t id, const Kernel::Serial &serial)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *item = dynamic_cast<Game::Building *>(this->_elements[id]);
  if (item == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (serial != item->frontQueue()) {
    Logger::getInstance()->log("Bug game_unitHasBeenProduct ?");
  }
  item->popQueue();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitPutInProduction(Kernel::ID::id_t id, const Kernel::Serial &serial, unsigned int)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *item = dynamic_cast<Game::Building *>(this->_elements[id]);
  if (item == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  item->addToQueue(serial);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitHasBeenDeletedFromProductionList(Kernel::ID::id_t id, const Kernel::Serial &serial)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *item = dynamic_cast<Game::Building *>(this->_elements[id]);
  if (item == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  item->removeFromQueue(serial);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_buildingBuilt(Kernel::ID::id_t id)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *item = dynamic_cast<Game::Building *>(this->_elements[id]);
  if (item == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  item->setBuilt();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitStopBuilding(Kernel::ID::id_t unitID, Kernel::ID::id_t buildingID)
{
  if (!itemExist(buildingID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *building = dynamic_cast<Game::Building *>(this->_elements[buildingID]);
  if (building == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *unit = dynamic_cast<Game::Building *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  building->removeBuilder(unitID);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitBuilding(Kernel::ID::id_t unitID, Kernel::ID::id_t buildingID)
{
  if (!itemExist(buildingID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *building = dynamic_cast<Game::Building *>(this->_elements[buildingID]);
  if (building == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *unit = dynamic_cast<Game::Building *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  building->addBuilder(unitID);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitMoveRessource(Kernel::ID::id_t id, unsigned int gold, unsigned int wood,
					       unsigned int food)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Unit *item = dynamic_cast<Game::Unit *>(this->_elements[id]);
  if (item == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  item->setRessources(Game::Ressources::GOLD, gold);
  item->setRessources(Game::Ressources::WOOD, wood);
  item->setRessources(Game::Ressources::FOOD, food);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitHarvest(Kernel::ID::id_t unitID, Kernel::ID::id_t ressSpotID)
{
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Unit *unit = dynamic_cast<Game::Unit *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(ressSpotID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::RessourcesSpot *spot = dynamic_cast<Game::RessourcesSpot *>(this->_elements[ressSpotID]);
  if (spot == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  spot->addHarvester(unitID);
  unit->setSpot(ressSpotID);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitEndStopingToHarvest(Kernel::ID::id_t unitID)
{
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Unit *unit = dynamic_cast<Game::Unit *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitWaitToHarvest(Kernel::ID::id_t unitID)
{
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Unit *unit = dynamic_cast<Game::Unit *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitStopHarvest(Kernel::ID::id_t unitID)
{
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Unit *unit = dynamic_cast<Game::Unit *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(unit->getSpot())) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::RessourcesSpot *spot = dynamic_cast<Game::RessourcesSpot *>(this->_elements[unit->getSpot()]);
  if (spot == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  spot->removeHarvester(unitID);
  unit->setSpot(0);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_unitDeposit(Kernel::ID::id_t unitID, Kernel::ID::id_t buildingID)
{
  if (!itemExist(buildingID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *building = dynamic_cast<Game::Building *>(this->_elements[buildingID]);
  if (building == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (!itemExist(unitID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::Building *unit = dynamic_cast<Game::Building *>(this->_elements[unitID]);
  if (unit == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_playerAmelioration(Kernel::ID::id_t id, const Kernel::Serial &type,
						const Kernel::Serial &serial)
{
  Game::Player *player = _players[id];
  if (player == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  player->addAmelioration(type, serial);
  if (itemExist(_UnitSelectedId)) {
    if (_elements[_UnitSelectedId]->serial() == type) {
      Kernel::ID::id_t focus = _UnitSelectedId;
      this->guigProfile_unFocus();
      this->guigProfile_focus(focus);
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_ameliorationProduct(Kernel::ID::id_t id, const Kernel::Serial &type,
						 const Kernel::Serial &amelioration, unsigned int)
{
  Game::Player *player = _players[id];
  if (player == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  player->addToQueue(type, amelioration);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_ameliorationDeletedFromProductionList(Kernel::ID::id_t id, const Kernel::Serial &type,
								   const Kernel::Serial &amelioration)
{
  Game::Player *player = _players[id];
  if (player == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  if (player->frontQueue(type) != amelioration) {
    Logger::getInstance()->log("Bug dans ameliorationDeletedFromProductionList");
  }
  (void) player->popQueue(type);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_ping(Kernel::ID::id_t, double, double)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_itemAttackItem(Kernel::ID::id_t fromID, Kernel::ID::id_t toID)
{
  if (!itemExist(fromID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  Game::CanUseCapacity *from = dynamic_cast<Game::CanUseCapacity *>(this->_elements[fromID]);
  if (from == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  if (!itemExist(toID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  Game::CanUseCapacity *to = dynamic_cast<Game::CanUseCapacity *>(this->_elements[toID]);
  if (to == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  from->setTarget(to->getID(), to->getType());
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_itemAttackZone(Kernel::ID::id_t fromID, double x, double y, double z)
{
  if (!itemExist(fromID)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  Game::CanUseCapacity *from = dynamic_cast<Game::CanUseCapacity *>(this->_elements[fromID]);
  if (from == NULL) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
    return ;
  }
  from->setTarget(x, y, z);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_itemUseCapacityOnZone(Kernel::ID::id_t, double, double, double, const Kernel::Serial &)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_itemUseCapacityOnItem(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_capacityUsed(Kernel::ID::id_t, const Kernel::Serial &)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_capacityOnAutoOrNot(Kernel::ID::id_t id, const Kernel::Serial &serial, bool automatic)
{
  if (!itemExist(id)) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  Game::AElement *item = this->_elements[id];
  if (item->hasCapacity(serial) == false) {
    __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, false);
    return ;
  }
  item->setCapacityAutomatic(serial, automatic);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::game_changeDayNight(bool day)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  this->daynight->setDate(day ? 9 : 22, 0, 0);
  this->_map->setDayNight(day);
}

const Game::Team*  GUIG::Controller::teamExist(unsigned int teamID)
{
  if (teams.find(teamID) == teams.end())
  {
    teams[teamID] = new Game::Team();
    teams[teamID]->init();
  }
  for (auto it : teams) {
    std::cout << "team" << it.first << ": " << it.second << std::endl;
  }
  return (teams[teamID]);
}

void  GUIG::Controller::game_createNewPlayer(Kernel::ID::id_t id, unsigned int teamID, const Kernel::Serial & race)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  Game::Player  *player = new Game::Player();
  player->init(id, (Game::Controller::getInstance())->getRace(race), teamExist(teamID));
  teams[teamID]->addPlayer(player);
  _players[id] = player;
  if (id == _idPlayerTMP) {
    _player = _players[id];
    Race::Race r;
    std::string rname = (Game::Controller::getInstance()->getRace(race)->getName());
    if (rname == "GENICIA")
      ressource->setRace(Race::GENICIA);
    else if (rname == "HUMANOIDE")
      ressource->setRace(Race::HUMANOIDE);
    else if (rname == "IMPERIUM")
      ressource->setRace(Race::IMPERIUM);
    else if (rname == "Random")
      ressource->setRace(Race::RANDOM);
    ressource->setGold(_player->getRessources(Game::Ressources::GOLD));
    ressource->setWood(_player->getRessources(Game::Ressources::WOOD));
    ressource->setFood(_player->getRessources(Game::Ressources::FOOD));
  }
}

void  GUIG::Controller::game_setYouAre(Kernel::ID::id_t id)
{
  _player = _players[id];
  _idPlayerTMP = id;
  if (_player) {
    ressource->setGold(_player->getRessources(Game::Ressources::GOLD));
    ressource->setWood(_player->getRessources(Game::Ressources::WOOD));
    ressource->setFood(_player->getRessources(Game::Ressources::FOOD));
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

// CAMERA

void  GUIG::Controller::initCamera()
{
  this->_camera->setPosition(Ogre::Vector3(-5.0f, 180.0f, -0.5f));
  this->_camera->lookAt(Ogre::Vector3(-5.0f, 0.0f, -0.5f));
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::moveCameraLeft()
{
  Ogre::Vector3 v = this->_camera->getPosition();
  v.x -= 0.7;
  if (!_map || v.x < -5)
    return;
  float x = static_cast<float>(v.x);
  float coeff_x = static_cast<float>((_map->x + 7) * 3 * GUIG_SIZE_MAP_X) / static_cast<float>(4);
  float y = static_cast<float>(v.z);
  float coeff_y = (_map->y + 5) * GUIG_SIZE_MAP_Y;
  minimap->moveLook(Ogre::Vector2(x / coeff_x, y / coeff_y));
  this->_camera->setPosition(v);
}

void  GUIG::Controller::moveCameraRight()
{
  Ogre::Vector3 v = this->_camera->getPosition();
  v.x += 0.7;
  if (!_map || v.x > (_map->x + 7) * 3 * GUIG_SIZE_MAP_X / 4)
    return;
  float x = static_cast<float>(v.x);
  float coeff_x = static_cast<float>((_map->x + 7) * 3 * GUIG_SIZE_MAP_X) / static_cast<float>(4);
  float y = static_cast<float>(v.z);
  float coeff_y = (_map->y + 5) * GUIG_SIZE_MAP_Y;
  minimap->moveLook(Ogre::Vector2(x / coeff_x, y / coeff_y));
  this->_camera->setPosition(v);
}

void  GUIG::Controller::moveCameraDown()
{
  Ogre::Vector3 v = this->_camera->getPosition();
  v.z += 0.7;
  if (!_map || v.z > (_map->y + 5) * GUIG_SIZE_MAP_Y)
    return;
  float x = static_cast<float>(v.x);
  float coeff_x = static_cast<float>((_map->x + 7) * 3 * GUIG_SIZE_MAP_X) / static_cast<float>(4);
  float y = static_cast<float>(v.z);
  float coeff_y = (_map->y + 5) * GUIG_SIZE_MAP_Y;
  minimap->moveLook(Ogre::Vector2(x / coeff_x, y / coeff_y));
  this->_camera->setPosition(v);
}

void  GUIG::Controller::moveCameraUp()
{
  Ogre::Vector3 v = this->_camera->getPosition();
  v.z -= 0.7;
  if (!_map || v.z < 0.5)
    return;
  float x = static_cast<float>(v.x);
  float coeff_x = static_cast<float>((_map->x + 7) * 3 * GUIG_SIZE_MAP_X) / static_cast<float>(4);
  float y = static_cast<float>(v.z);
  float coeff_y = (_map->y + 5) * GUIG_SIZE_MAP_Y;
  minimap->moveLook(Ogre::Vector2(x / coeff_x, y / coeff_y));
  this->_camera->setPosition(v);
}

void  GUIG::Controller::controllerEmpty(const std::string &name)
{
  guigProfile_unFocus();
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::actionClickSpecial(const std::string &name)
{
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
  Kernel::ID::id_t id;
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
  if (prec == "partialMap")
  {
    int pos2 = next.find("_");
    std::string prec2 = "";
    std::string next2 = "";
    if (pos2 > 0 && pos2 < next.size())
    {
      prec2 = next.substr(0, pos2);
      next2 = next.substr(pos2 + 1);
    }
    else
      prec2 = "";
    int r = toValue<int>(next2);
    int x = r % _map->x;
    int y = r / _map->y;
    if (_actClickAction == GUIG::Controller::CAPATOZONE)
      guigProfile_actionCapaToZone(x, y);
    else if (_actClickAction == GUIG::Controller::ATTACKTOZONE)
      guigProfile_actionAttackToZone(x, y);
    else if (_actClickAction == GUIG::Controller::CREATEBUILDING)
      guigProfile_actionCreateBuilding(x, y);
    else if (_actClickAction == GUIG::Controller::UNITPATROL)
      guigProfile_actionUnitPatrol(x, y);
  }
  else if (0 != (id = element3D_findElement("element3D_" + name)))
  {
    if (_elements.find(id) != _elements.end() &&
        _elements[id])
    {
      if (_actClickAction == GUIG::Controller::CAPATOUNIT)
        guigProfile_actionCapaToUnit(id);
      else if (_actClickAction == GUIG::Controller::CAPATOZONE)
        guigProfile_actionCapaToZone(id);
      else if (_actClickAction == GUIG::Controller::ATTACKTOZONE)
        guigProfile_actionAttackToZone(id);
      else if (_actClickAction == GUIG::Controller::ATTACKTOUNIT)
        guigProfile_actionAttackToUnit(id);
      else if (_actClickAction == GUIG::Controller::CREATEBUILDING)
        guigProfile_actionCreateBuilding(id);
      else if (_actClickAction == GUIG::Controller::UNITPATROL)
        guigProfile_actionUnitPatrol(id);
    }
  }
  else
    std::cout << "Undefined actionClick" << std::endl;
}

void  GUIG::Controller::actionClick(const std::string &name)
{
  Kernel::ID::id_t id;
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
  if (prec == "partialMap")
  {
    int pos2 = next.find("_");
    std::string prec2 = "";
    std::string next2 = "";
    if (pos2 > 0 && pos2 < next.size())
    {
      prec2 = next.substr(0, pos2);
      next2 = next.substr(pos2 + 1);
    }
    else
      prec2 = "";
    int r = toValue<int>(next2);
    int x = r % _map->x;
    int y = r / _map->y;
    unitSelectedMoveToPosition(x, y);
  }
  else if (0 != (id = element3D_findElement(name)))
  {
    if (_elements.find(id) != _elements.end() &&
        _elements[id])
    {
      Game::Type type = Kernel::Manager::getInstance()->getData(_elements[id]->serial())->type;
      if (type == Game::BUILDING && _player == _elements[id]->getPlayer() && !_elements[id]->isBuilt())
      {
        unitBuilt(id);
        // dans ma team + en construction;
      }
      else if (type == Game::UNIT || type == Game::BUILDING)
        unitSelectedAttackId(id);
      else if (type == Game::RESSSPOT)
        harvestUnitSelected(id);
    }
  }
  else
    std::cout << "Undefined actionClick :: name(" << name << ")" << std::endl;
}

void  GUIG::Controller::unitBuilt(Kernel::ID::id_t id)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_UnitSelectedId == 0 || _elements.find(_UnitSelectedId) == _elements.end() || _elements[_UnitSelectedId] == NULL)
    return;
  if (ids.size() == 1)
    callback_unitBuild(_UnitSelectedId, id);
  else
    callback_unitsBuild(ids, id);
}

void  GUIG::Controller::harvestUnitSelected(Kernel::ID::id_t id)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  bool trb = false;


  if (ids.size() == 1)
  {
    trb = true;
    callback_unitHarvest(*(ids.begin()), id);
  }
  else if (ids.size() > 1)
  {
    trb = true;
    callback_unitsHarvest(ids, id);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUIG::Controller::unitSelectedAttackId(Kernel::ID::id_t id)
{
  bool trb = false;
  if (_UnitSelectedId != 0 && _UnitIsSelected && _elements.find(_UnitSelectedId) != _elements.end() && _elements[_UnitSelectedId])
  {
    trb = true;
    callback_itemAttack(_UnitSelectedId, id);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUIG::Controller::unitSelectedMoveToPosition(int x, int y)
{
  bool trb = false;
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  if (ids.size() > 1)
  {
    trb = true;
    const Vector3d &v = this->_map->getHexa(x, y);
    callback_moveItems(ids, true, v.x + this->_map->_hexaX, v.y + this->_map->_hexaY, v.z);
  }
  else if (_UnitIsSelected && _UnitSelectedId != 0 && _elements.find(_UnitSelectedId) != _elements.end() && _elements[_UnitSelectedId] && _map)
  {
    trb = true;
    const Vector3d &v = this->_map->getHexa(x, y);
    callback_moveItem(_UnitSelectedId, v.x + this->_map->_hexaX, v.y + this->_map->_hexaY, v.z);
  }
  std::cout << _UnitIsSelected << "id <> find:" << ( _elements.find(_UnitSelectedId) != _elements.end()) << "NULL " << _elements[_UnitSelectedId] << " map ?" << _map << "std::endl;" << std::endl;;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, trb);
}

void  GUIG::Controller::click(std::string const &name)
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
  if (CONTROLLER_FCT.find(prec) != CONTROLLER_FCT.end())
  {
    (this->*CONTROLLER_FCT[prec])(next);
  }
  else
  {
   (this->*CONTROLLER_FCT["controllerEmpty"])(prec);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::controllerCreateMap()
{
  _soleil = _sceneMgr->createLight("light_soleilGeneral");
  _soleil->setType(Ogre::Light::LT_DIRECTIONAL);
  _soleil->setDirection(10.0, -20.0, -5);
  for (unsigned int j = 0; j < _map->y; ++j)
    {
      for (unsigned int i = 0; i < _map->x; ++i)
	{
	  int p = j * _map->x + i;
	  //mapGraph[p]->getLight()->setVisible(false);
	  const Vector3d &v = this->_map->getHexa(i, j);
	  mapGraph[p] = new Element3DContainer();
	  mapGraph[p]->init(this->_sceneMgr, "partialMap_nb_" + toString(p) , "hexagon.mesh", NULL, "partialMap_nb_" + toString(p));
	  double x = GUIG_SIZE_MAP_X * (v.x + this->_map->_hexaX);
	  double z = (v.y + this->_map->_hexaY) * GUIG_SIZE_MAP_Y;
	  double y = 0;
	  mapGraph[p]->setPos(x, y, z);
	  mapGraph[p]->setOrientation(-90);
	  float e = 10.0f;
	  mapGraph[p]->getNode()->setScale(1.0, 1.0, 1.0);
	  mapGraph[p]->getNode()->setScale(e, e * _map->getHeight(i, j), e);
	  if (!(_map->getHeight(i, j) > 0))
	    mapGraph[p]->getNode()->setVisible(false);
	}
    }
  _mapIsInit = true;
}

// __PROGRESS__
//

void  GUIG::Controller::progress_function(const std::string &name)
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
  if (progress_fct.find(prec) != progress_fct.end())
  {
    (this->*progress_fct[prec])(next);
  }
}

void  GUIG::Controller::progress_receivePlayerInRoom(const std::string &pseudo,
                      int team, Race::Race race, bool ready)
{
  progress->infoMember(pseudo, team, race);
  allymenu->addPlayer(pseudo, team);
  if (ready)
  {
    progress->getReadyMember(pseudo);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::progress_receiveReadyPlayer(const std::string &pseudo)
{
  progress->getReadyMember(pseudo);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::progress_loadFile(const std::string &name)
{
  std::vector<Kernel::Serial> v;
  // LOADFILE
  containerRace = parserRace.parse("./races/" + name , v);
  fileName = "./races/" + name;
  for (auto &it : containerRace)
  {
    if (it.second != NULL)
    {
      (Game::Controller::getInstance())->addRace(fileName, it.second);
      // it.second->dump();
    }
    else
      std::cout << "Y a un truck null c'est cheloux" << std::endl;
  }
  elementPoolManager.init(this->_sceneMgr, v);
  this->_map = Parser::Map::getInstance()->parse("./races/" + name);

  // DEBUGG
  if (!this->_map)
    std::cout << "Y a de la merde quelque part" << std::endl;

  controllerCreateMap();
  initCamera();

  // NETWORK
  Protocol::Job *job2 = Factory::Protocol::Job::create();
  job2->iAmReady();
  Network::Manager::Client::getInstance()->push(job2);
}

void  GUIG::Controller::progress_receiveFileExist(const std::string &name)
{
  std::ifstream file("./races/" + name);
  if (!file.fail())
  {
    std::cout << "file existant !!" << std::endl;
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->fileExists(name, true);
    //  std::cout << "FILE EXIST" << std::endl;
    Network::Manager::Client::getInstance()->push(job);
    progress_loadFile(name);
  }
  else
  {
    std::cout << "file non existant !!" << std::endl;
    // NETWORK
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->fileExists(name, false);
    Network::Manager::Client::getInstance()->push(job);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void		GUIG::Controller::zoomMinimap(char zoom)
{
  if (zoom > 0 && minimap->canScrollDown())
  {
    Ogre::Vector3 v = _camera->getPosition();
    v.y += 20.0f;
    _camera->setPosition(v);
    (*minimap)++;
  }
  else if (minimap->canScrollUp())
  {
    Ogre::Vector3 v = _camera->getPosition();
    v.y -= 20.0f;
    _camera->setPosition(v);
    (*minimap)--;
  }
}

// __MINIMAP__
//

void  GUIG::Controller::minimap_function(const std::string &name)
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
  if (minimap_fct.find(prec) != minimap_fct.end())
  {
    (this->*minimap_fct[prec])(next);
  }
}

void  GUIG::Controller::minimap_moveLook(const std::string &name)
{
  const Ogre::Vector2 &posMinimap = minimap->getPosition();
  const Ogre::Vector2 &sizeMinimap = minimap->getSize();
  minimap->moveLook(Ogre::Vector2((mousePosition.x - (posMinimap.x * _window->getWidth())) / sizeMinimap.x,
                                  (mousePosition.y - (posMinimap.y * _window->getHeight())) / sizeMinimap.y));
  Ogre::Vector3 v = this->_camera->getPosition();
  const Ogre::Vector2 &pos = minimap->getLookPosition();
  v.z = pos.y * ((_map->y + 5) * GUIG_SIZE_MAP_Y);
  v.x = pos.x * (static_cast<float>((_map->x + 7)) * static_cast<float>(GUIG_SIZE_MAP_X) * 3.0 / 4.0);
  this->_camera->setPosition(v);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

// __RESSOURCE__
//

void  GUIG::Controller::ressource_function(const std::string &name)
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
  if (ressource_fct.find(prec) != ressource_fct.end())
  {
    (this->*ressource_fct[prec])(next);
  }
}


// GUIG PROFILE_HPP

void  GUIG::Controller::guigProfile_actionCapaToZone(int x, int y)
{
  const Vector3d &value = this->_map->getHexa(x,y);

  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  callback_useCapacityZone(_UnitSelectedId, _serialAction, value.x, value.y, value.z);
}

void  GUIG::Controller::guigProfile_actionCapaToZone(Kernel::ID::id_t id)
{
  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  callback_useCapacityZone(_UnitSelectedId, _serialAction, _elements[id]->getX(),
                            _elements[id]->getY(), _elements[id]->getZ());
}

void  GUIG::Controller::guigProfile_actionCapaToUnit(Kernel::ID::id_t id)
{
  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  callback_itemUseCapacity(_UnitSelectedId, id, _serialAction);
}

void  GUIG::Controller::guigProfile_actionAttackToZone(int x, int y)
 {
  const Vector3d &value = this->_map->getHexa(x, y);
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;

  if (ids.size() == 1)
    callback_itemAttackZone(_UnitSelectedId, value.x, value.y, value.z);
  else if (ids.size() > 1)
    callback_itemsAttackZone(ids, value.x, value.y, value.z);
}

void  GUIG::Controller::guigProfile_actionAttackToZone(Kernel::ID::id_t id)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;

  if (ids.size() == 1)
    callback_itemAttackZone(_UnitSelectedId, _elements[id]->getX(), _elements[id]->getY(), _elements[id]->getZ());
  else if (ids.size() > 1)
    callback_itemsAttackZone(ids, _elements[id]->getX(), _elements[id]->getY(), _elements[id]->getZ());
}

void  GUIG::Controller::guigProfile_actionAttackToUnit(Kernel::ID::id_t id)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;

  if (ids.size() == 1)
    callback_itemAttack(_UnitSelectedId, id);
  else if (ids.size() > 1)
    callback_itemsAttack(ids, id);
}

void  GUIG::Controller::guigProfile_actionCreateBuilding(int x, int y)
{
  const Vector3d &value = this->_map->getHexa(x, y);

  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  callback_createBuilding(_serialAction, value.x, value.y, value.z, 0);
}

void  GUIG::Controller::guigProfile_actionCreateBuilding(Kernel::ID::id_t id)
{
  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  callback_createBuilding(_serialAction, _elements[id]->getX(), _elements[id]->getY(), _elements[id]->getZ(), 0);
}

void  GUIG::Controller::guigProfile_actionUnitPatrol(int x, int y)
{
  const Vector3d &value = this->_map->getHexa(x, y);
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  callback_unitPatrol(_UnitSelectedId, value.x, value.y);

  if (ids.size() == 1)
    callback_unitPatrol(_UnitSelectedId, value.x, value.y);
  else if (ids.size() > 1)
    callback_unitsPatrol(ids, value.x, value.y, true);
}

void  GUIG::Controller::guigProfile_actionUnitPatrol(Kernel::ID::id_t id)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();

  if (_elements.find(id) == _elements.end() || !_elements[id])
    return;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;

  if (ids.size() == 1)
    callback_unitPatrol(_UnitSelectedId, _elements[id]->getX(), _elements[id]->getY());
  else if (ids.size() > 1)
    callback_unitsPatrol(ids, _elements[id]->getX(), _elements[id]->getY(), true);
}

void  GUIG::Controller::guigProfile_function(const std::string &name)
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
  if (guigProfile_fct.find(prec) != guigProfile_fct.end())
  {
    (this->*guigProfile_fct[prec])(next);
  }
}

void  GUIG::Controller::guigProfile_capacities(const std::string &name)
{
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  int pos = name.find("_");
  std::string serial = "";
  std::string position = "";
  if (pos > 0 && pos < name.size())
  {
    serial = name.substr(0, pos);
    position = name.substr(pos + 1);
  }
  else
    serial = name;
  Game::Type type = Kernel::Manager::getInstance()->getData(serial)->type;
  if (_MB_RIGHT)
  {
    if (type == Game::CAPACITY)
    {
      const Kernel::CapacityData *capaData = Kernel::Manager::getInstance()->getCapacityData(serial);
      if (capaData->canAuto)
      {
        callback_automaticCapacity(_UnitSelectedId, serial, !capaData->isAuto);
      }
    }
  }
  else
  {
    if (type == Game::CAPACITY)
    {
      const Kernel::CapacityData *capaData = Kernel::Manager::getInstance()->getCapacityData(serial);

      if (capaData->target == Game::Capacity::NONE)
      {
        callback_useCapacity(_UnitSelectedId, serial);
      }
      else if (capaData->target == Game::Capacity::ITEM)
      {
        _actClickModified = true;
        _serialAction = serial;
        _actClickAction = GUIG::Controller::CAPATOUNIT;
      }
      else if (capaData->target == Game::Capacity::ZONE)
      {
        _actClickModified = true;
        _serialAction = serial;
        _actClickAction = GUIG::Controller::CAPATOZONE;
      }
    }
    else if (type == Game::BUILDING)
    {
      _actClickModified = true;
      _serialAction = serial;
      _actClickAction = GUIG::Controller::CREATEBUILDING;
    }
    else if (type == Game::UNIT)
    {
      callback_produceUnit(_UnitSelectedId, serial);
    }
    else if (type == Game::AMELIORATION)
    {
      callback_produceAmelioration(_elements[_UnitSelectedId]->serial(), serial); // CREATE
    }
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::guigProfile_objects(const std::string &)
{
}

void  GUIG::Controller::guigProfile_effects(const std::string &)
{
  // Rien a faire normalement
}

void  GUIG::Controller::guigProfile_productions(const std::string &name)
{
  int pos = name.find("_");
  std::string serial = "";
  std::string position = "";
  if (pos > 0 && pos < name.size())
  {
    serial = name.substr(0, pos);
    position = name.substr(pos + 1);
  }
  else
    serial = name;
  if (_UnitSelectedId == 0 || _UnitIsSelected == false)
    return;
  Game::Type type = Kernel::Manager::getInstance()->getData(serial)->type;
  if (Game::UNIT == type)
  {
    callback_removeUnitFromProduction(_UnitSelectedId, serial);
  }
  else if (Game::HERO == type)
  {
    // Hero
  }
  else if (Game::AMELIORATION == type)
  {
    callback_removeAmeliorationFromProduction(_elements[_UnitSelectedId]->serial(), serial);
  }
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

// CALLBACK

void	GUIG::Controller::callback_moveItem(Kernel::ID::id_t id, double x, double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askMoveItem(id, x, y, z);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_moveItems(const std::vector<Kernel::ID::id_t> &ids, bool adapt,
					     double x, double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->moveItemGroup(x, y, z, adapt, ids);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_changeUnitStance(Kernel::ID::id_t id, Game::Stance::Type type) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->unitChangeStance(id, type);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_changeUnitsStance(const std::vector<Kernel::ID::id_t> &ids,
						     Game::Stance::Type stance) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->unitGrpStance(ids, stance);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_useCapacity(Kernel::ID::id_t id, const Kernel::Serial &capacity) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askActivateCapacity(id, capacity);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_produceUnit(Kernel::ID::id_t building, const Kernel::Serial &unit) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitProd(building, unit);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_stopItemAction(Kernel::ID::id_t id) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->itemStopAction(id);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_setItemAction(Kernel::ID::id_t id, Game::eAction action) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askSetItemAction(id, action);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_setItemsAction(const std::vector<Kernel::ID::id_t> &ids, Game::eAction action) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askSetItemsAction(action, ids);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_removeUnitFromProduction(Kernel::ID::id_t building, const Kernel::Serial &unit) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askRemoveUnitFromProduction(building, unit);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_heroPickUpObject(Kernel::ID::id_t hero, Kernel::ID::id_t object) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askHeroToTakeObject(hero, object);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_heroReleaseObject(Kernel::ID::id_t hero, Kernel::ID::id_t object,
						     double x, double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askHeroToReleaseObject(hero, object, x, y, z);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_removeAmeliorationFromProduction(const Kernel::Serial &type,
								    const Kernel::Serial &serial) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askRemoveAmeliorationFromProductionQueue(type, serial);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_produceAmelioration(const Kernel::Serial &type, const Kernel::Serial &serial) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askProduceAmelioration(type, serial);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitBuild(Kernel::ID::id_t unit, Kernel::ID::id_t building) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitToBuild(unit, building);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitHarvest(Kernel::ID::id_t unit, Kernel::ID::id_t spot) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitHarvest(unit, spot);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitsHarvest(const std::vector<Kernel::ID::id_t> &units, Kernel::ID::id_t spot) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitsHarvest(spot, units);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitsBuild(const std::vector<Kernel::ID::id_t> &units, Kernel::ID::id_t building) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitsToBuild(building, units);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_itemAttack(Kernel::ID::id_t from, Kernel::ID::id_t to) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemAttack(from, to);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_itemsAttack(const std::vector<Kernel::ID::id_t> &from, Kernel::ID::id_t to) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemsAttack(to, from);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_itemUseCapacity(Kernel::ID::id_t from, Kernel::ID::id_t to,
						   const Kernel::Serial &capacity) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemUseCapacity(from, to, capacity);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitPatrol(Kernel::ID::id_t id, double x, double y) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitPatrol(id, x, y);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_unitsPatrol(const std::vector<Kernel::ID::id_t> &ids, double x, double y,
					       bool adapt) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askUnitsPatrol(ids, x, y, adapt);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_itemAttackZone(Kernel::ID::id_t id, double x, double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemAttackZone(id, x, y, z);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_itemsAttackZone(const std::vector<Kernel::ID::id_t> &ids, double x,
						   double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemsAttackZone(ids, x, y, z);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_useCapacityZone(Kernel::ID::id_t id, const Kernel::Serial &capacity,
						   double x, double y, double z) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askItemUseZoneCapacity(id, capacity, x, y, z);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_automaticCapacity(Kernel::ID::id_t id, const Kernel::Serial &capacity,
						     bool automatic) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askAutomaticCapacity(id, capacity, automatic);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void	GUIG::Controller::callback_createBuilding(const Kernel::Serial &building, double x,
						  double y, double z, int o) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->askCreateBuilding(building, x, y, z, o);
  Network::Manager::Client::getInstance()->push(job);
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

void  GUIG::Controller::guigProfile_clean(const std::string &name)
{
  _UnitIsSelected = false;
  profile->clear();
}

void  GUIG::Controller::guigProfile_putIcon(Kernel::ID::id_t id)
{
  profile->profileSetIcon(_elements3D[id]->getIconName(), id, _elements[id]->serial());
}

void  GUIG::Controller::guigProfile_putCapacities(Kernel::ID::id_t id)
{
  const std::map<Kernel::Serial, Game::Capacity *> &capacitiesList =  _elements[id]->getCapacities();

  if (!_player || (_player && _player != _elements[id]->getPlayer()))
    return;
  for (std::map<Kernel::Serial, Game::Capacity *>::const_iterator it = capacitiesList.begin();
       it != capacitiesList.end(); ++it)
    {
      const Kernel::Data	*ptr = Kernel::Manager::getInstance()->getData(it->first);

      if (!ptr)
        throw graphicException(std::string("Ca ne devrait jamais Throw ici !") + __PRETTY_FUNCTION__ + " " + Converter::StringOf<int>(__LINE__));

    if (Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY) != it->first)
      profile->capacitiesElementPush(0, it->first, ptr->icon);
  }
  if ( _elements[id]->hasCapacity(Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY)))
    {
      const std::vector<Kernel::Serial> &buildings = _elements[id]->getRace()->getBuildings();
      for (std::vector<Kernel::Serial>::const_iterator it = buildings.begin(); it != buildings.end(); ++it)
	{
	  const Kernel::Data	*ptr = Kernel::Manager::getInstance()->getData(*it);

	  if (!ptr)
	    throw graphicException(std::string("Ca ne devrait jamais Throw ici !") + __PRETTY_FUNCTION__ + " " + Converter::StringOf<int>(__LINE__));

	  profile->capacitiesElementPush(0, *(it), ptr->icon);

	}
    }
  for (auto &it : Kernel::Manager::getInstance()->getData(_elements[id]->serial())->ameliorations)
  {
    const Kernel::Data *ptr = Kernel::Manager::getInstance()->getData(it);

    if (!ptr)
      throw graphicException("Ca ne devrait jamais Throw ici !");

    if (_elements[id]->getPlayer()->hasAmelioration(_elements[id]->serial(), it) == false) {
      profile->capacitiesElementPush(0, (it), ptr->icon);
    }
  }
  if (Game::BUILDING == _elements[id]->getType())
  {
    for (auto &it : Kernel::Manager::getInstance()->getBuildingData(_elements[id]->serial())->units)
    {
      const Kernel::Data *ptr = Kernel::Manager::getInstance()->getData(it);

      if (!ptr)
        throw graphicException(std::string("Ca ne devrait jamais Throw ici !") + __PRETTY_FUNCTION__ + " " + Converter::StringOf<int>(__LINE__));


      if (_elements[id]->getPlayer()->hasAmelioration(_elements[id]->serial(), it) == false) {
	profile->capacitiesElementPush(0, (it), ptr->icon);
      }
    }
  }
}

void  GUIG::Controller::guigProfile_putEffects(Kernel::ID::id_t id)
{
  const std::list<const Game::Effect *> &effectsList = _elements[id]->getTemporaryEffects();

  for (std::list<const Game::Effect *>::const_iterator it = effectsList.begin();
        it != effectsList.end(); ++it)
  {
    const Kernel::Data *ptr = Kernel::Manager::getInstance()->getData((*it)->serial());

    if (!ptr)
      throw graphicException("Ca ne devrait jamais Throw ici !");

    profile->effectsElementPush(0, (*it)->serial(), ptr->icon);
  }
}

void  GUIG::Controller::guigProfile_putProductions(Kernel::ID::id_t id)
{
  Game::Building  *ptr;
  if (!(ptr = dynamic_cast<Game::Building*>(_elements[id])))
    return;
  const std::deque<Kernel::Serial>  &productionsList = ptr->getProductionQueue()->getQueue();

  for (std::deque<Kernel::Serial>::const_iterator it = productionsList.begin();
        it != productionsList.end(); ++it)
  {
    const Kernel::Data *ptr = Kernel::Manager::getInstance()->getData((*it));

    if (!ptr)
      throw graphicException("Ca ne devrait jamais Throw ici !");

    profile->productionsElementPush(0, (*it), ptr->icon);
  }
}

void  GUIG::Controller::guigProfile_putObjects(Kernel::ID::id_t id)
{
  Game::Hero  *ptr;
  if (!(ptr = dynamic_cast<Game::Hero*>(_elements[id])))
    return;
  const std::list<Game::Object *>  &objectsList = ptr->getObjects();

  for (std::list<Game::Object *>::const_iterator it = objectsList.begin();
        it != objectsList.end(); ++it)
  {
    const Kernel::Data *ptr = Kernel::Manager::getInstance()->getData((*it)->serial());

    if (!ptr)
      throw graphicException("Ca ne devrait jamais Throw ici !");

    profile->objectsElementPush(0, (*it)->serial(), ptr->icon);
  }
}

void  GUIG::Controller::guigProfile_unFocus()
{
  guigProfile_clean();
  squad->clear();
  annotation->hideAll();
  annotation->setVisible(false);
  profile->draw();
}

void  GUIG::Controller::guigProfile_focus(Kernel::ID::id_t id)
{

  guigProfile_clean();
  if (!_KC_CTRL)
  {
    squad->clear();
  }
  else
    std::cout << "KC NOT PRESSEDD" << std::endl;

  if (itemExist(id)) {
    if (_elements[id]->getPlayer() != _player)
    {
      squad->clear();
    }
    const Kernel::Data	*ptr = Kernel::Manager::getInstance()->getData(_elements[id]->serial());

    _UnitIsSelected = true;
    _UnitSelectedId = id;
    if (_elements[id]->getPlayer() == _player)
      squad->addUnit(ptr->icon, id, _elements[id]->serial());
    guigProfile_putIcon(id);
    guigProfile_putCapacities(id);
    guigProfile_putObjects(id);
    guigProfile_putProductions(id);
    guigProfile_putEffects(id);

    annotation->update(this->_elements[id]);
    annotation->setVisible(true);
  }

  profile->draw();
}

// GUIG SQUAD_HPP
void  GUIG::Controller::guigSquad_function(const std::string &name)
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
  if (guigSquad_fct.find(prec) != guigSquad_fct.end())
  {
    (this->*guigSquad_fct[prec])(next);
  }
}

void  GUIG::Controller::guigSquad_round(const std::string &name)
{
  _actClickAction = GUIG::Controller::UNITPATROL;
  _serialAction = "";
}

void  GUIG::Controller::guigSquad_shield(const std::string &name)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  if (ids.size() == 1)
  {
    std::cout << "ids[0]:" << ids[0] << std::endl;
    callback_changeUnitStance(ids[0], Game::Stance::DEFENSIVE);
  }
  else if (ids.size() > 1)
  {
    callback_changeUnitsStance(ids, Game::Stance::DEFENSIVE);
  }
}

void  GUIG::Controller::guigSquad_attack(const std::string &name)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  if (ids.size() == 1)
  {
    std::cout << "ids[0]:" << ids[0] << std::endl;
    callback_changeUnitStance(ids[0], Game::Stance::OFFENSIVE);
  }
  else if (ids.size() > 1)
  {
    callback_changeUnitsStance(ids, Game::Stance::OFFENSIVE);
  }
}

void  GUIG::Controller::guigSquad_alert(const std::string &name)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  if (ids.size() == 1)
  {
    std::cout << "ids[0]:" << ids[0] << std::endl;
    callback_changeUnitStance(ids[0], Game::Stance::NEUTRAL);
  }
  else if (ids.size() > 1)
  {
    callback_changeUnitsStance(ids, Game::Stance::NEUTRAL);
  }
}

void  GUIG::Controller::guigSquad_cancel(const std::string &name)
{
  const std::vector<Kernel::ID::id_t> &ids = squad->get_idUnits();
  for (unsigned int i = 0; i < ids.size(); i++)
    callback_stopItemAction(ids[i]);
}

// element3D_HPP

Kernel::ID::id_t  GUIG::Controller::element3D_findElement(const std::string &name)
{
  for (std::map<Kernel::ID::id_t, Element3DContainer*>::iterator it = _elements3D.begin();
      it != _elements3D.end(); ++it)
    if ((it->second)->getName() == name)
      return (it->first);
  return (0);
}

void  GUIG::Controller::element3D_function(const std::string &name)
{
  Kernel::ID::id_t id = element3D_findElement("element3D_" + name);
  if (id == 0)
  {
    std::cout << "Unknown type" << std::endl;
    return;
  }
  if (_elements.find(id) != _elements.end() && _elements3D.find(id) != _elements3D.end() &&
      _elements[id] != NULL && _elements3D[id] != NULL)
  {
    std::cout << "Type trouve !!" << std::endl;
    guigProfile_focus(id);
  }
  else
    std::cout << "Element null ou introuvable" << std::endl;
  __CALL_FUNCTION_DEBUG__(__FILE__, __PRETTY_FUNCTION__, __LINE__, true);
}

// GUIG_CHATBOX_HPP

void  GUIG::Controller::guigChatbox_function(const std::string &name)
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
  if (guigChatbox_fct.find(prec) != guigChatbox_fct.end())
  {
    (this->*guigChatbox_fct[prec])(next);
  }
}

void  GUIG::Controller::guigChatbox_input(const std::string &)
{
  this->chatbox->sendMsg();
}

void  GUIG::Controller::guigChatbox_recvGrpMsg(const std::string &from, const std::string &msg)
{
  chatbox->recvGrpMsg(from, msg);
}

void  GUIG::Controller::guigChatbox_recvMsgGlob(const std::string &from, const std::string &msg)
{
  chatbox->recvMsgGlob(from, msg);
}

void  GUIG::Controller::guigChatbox_recvWhisp(const std::string &from, const std::string &msg) {
  chatbox->recvWhisp(from, msg);
}
