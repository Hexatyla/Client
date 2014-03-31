//
// Application.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Fri Jan 24 15:34:46 2014 Yannick Briffa
// Last update Fri Mar 21 17:23:28 2014 geoffrey bauduin
//

#include	"applications/Application.hh"
#include	"overlays/MouseOverlayManager.hh"
#include	"Algo/MD5.hpp"
#include	"Factory/Factory.hpp"
#include	"Factory/Protocol.hpp"
#include	"Singleton.hpp"
#include	"Logger.hpp"
#include	"Network/Manager/Client.hpp"
#include	"Network/Exception.hpp"
#include	"Factory/Client.hpp"

Application::Application()
  : _exit(false), _root(NULL), _plugins(Ogre::StringUtil::BLANK), _ressources(Ogre::StringUtil::BLANK), _window(NULL), _fontmanager(NULL),_inputmanager(NULL), _mouse(NULL), _keyboard(NULL), _overlaySystem(NULL), _currentScene(NULL), _cursorOverlay(NULL), _mousecursor(NULL), _thNetwork(new Thread)
{
  (void) ::Logger::getInstance();
  (void) ::Algo::MD5::getInstance();
  (void) ::Network::Manager::Client::getInstance();
}

Application::~Application()
{
  if (_window) {
    Ogre::WindowEventUtilities::removeWindowEventListener(_window, this);
    windowClosed(_window);
  }
  if (_root)
    delete _root;
  ::Logger::deleteInstance();
  ::Algo::MD5::deleteInstance();
  ::Network::Manager::Client::deleteInstance();
}

void		Application::loadResources()
{
  Ogre::ConfigFile	cf;
  Ogre::String		secName, typeName, archName;
  Ogre::ConfigFile::SettingsMultiMap	*settings;

  cf.load(_ressources);

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      settings = seci.getNext();
      for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
	}
    }
}

void		Application::initScene()
{
  std::cout << "*******   Initializating Scene    ********" << std::endl;
  AScene	*tmp;

  if (!(tmp = new GUI::Controller(_window)))
    throw graphicException("Failed to create MenuScene");
  _sceneMap[tmp->getName()] = tmp;

  if (!(tmp = new GUIG::Controller(_window)))
    throw graphicException("Failed to create ControllerGUIGScene");
  _sceneMap[tmp->getName()] = tmp;

  for (std::map<std::string, AScene *>::iterator it = _sceneMap.begin(); it != _sceneMap.end(); ++it)
    if ((*it).second != NULL)
    {
      ((*it).second)->init(_root);
      ((*it).second)->setVisible(false);
    }
}

void		Application::initInput()
{
  std::cout << "*******   Initializating Input    ********" << std::endl;
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

  OIS::ParamList	pl;
  size_t		value = 0;
  std::ostringstream	oss;

  _window->getCustomAttribute("WINDOW", &value);
  oss << value;
  pl.insert(std::make_pair(std::string("WINDOW"), oss.str()));

  if (!(_inputmanager = OIS::InputManager::createInputSystem(pl)))
    throw graphicException("failed to create input system");

  _keyboard = static_cast<OIS::Keyboard*>(_inputmanager->createInputObject( OIS::OISKeyboard, true ));
  _mouse = static_cast<OIS::Mouse*>(_inputmanager->createInputObject( OIS::OISMouse, true ));

  if (!_keyboard || !_mouse)
    throw graphicException("failed to connect input devices");

}

void		Application::initOverlaySceneManager()
{
  std::cout << "*******   Initializating Overlays    ********" << std::endl;
  _cursorOverlay = new MouseOverlayManager();
  _cursorOverlay->init(_window->getWidth(), _window->getHeight());
  _mousecursor = dynamic_cast<OverlayImage *>(_cursorOverlay->getOverlay("menuCursor"));
}

bool		Application::init(const std::string &host, int port)
{
  _plugins = "plugins.cfg";
  _ressources = "resources.cfg";
  Factory::init();
  Factory::Client::init();

  if (!(_root = new Ogre::Root(_plugins)))
    throw graphicException("fail init root");
  this->loadResources();

  if (!(_root->restoreConfig() || _root->showConfigDialog()))
    return false;

  if (!(_window = _root->initialise(true, "Hexatyla")))
    throw graphicException("can't initialise window renderer");


  if (!_fontmanager)
    _fontmanager = new Ogre::FontManager();

  if (!(_overlaySystem = new Ogre::OverlaySystem()))
    throw graphicException("Failed to instanciate OverlaySystem");

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  this->initInput();
  this->initScene();

  windowResized(_window);

  this->initOverlaySceneManager();

  bool		pb = false;

  Kernel::Manager::getInstance()->init();
  try {
    Network::Manager::Client::getInstance()->init(host, port);
  }
  catch (Network::Exception *e) {
    Logger::getInstance()->log(e->what(), Logger::FATAL);
    delete (e);
    pb = true;
  }
  if (pb == false) {
    this->_thNetwork->start(&start_network_manager, Network::Manager::Client::getInstance());
  }

  return true;
}

void		Application::reconnect() {
  delete (this->_thNetwork);
  this->_thNetwork = NULL;

  Network::Manager::Client::getInstance()->reconnect();
  this->_thNetwork = new Thread();
  this->_thNetwork->start(&start_network_manager, Network::Manager::Client::getInstance());
}

bool		Application::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  if (_exit || !_window || _window->isClosed())
    return false;

  if (!_currentScene) {
    std::cerr << "No more scene o display" << std::endl;
    return false;
  }

  _mouse->capture();
  _keyboard->capture();

  return _currentScene->updateFrame(evt);
}

void		Application::windowResized(Ogre::RenderWindow* rw)
{
  const OIS::MouseState &ms = _mouse->getMouseState();
  unsigned int		width, height, depth;
  int			left, top;

  rw->getMetrics(width, height, depth, left, top);
  ms.width = width;
  ms.height = height;
  if (_cursorOverlay)
    _cursorOverlay->updateWindowDimension(rw->getWidth(), rw->getHeight());
}

void		Application::windowClosed(Ogre::RenderWindow* rw)
{
  if (rw == _window)
    {
      if (_inputmanager)
        {
	  _inputmanager->destroyInputObject( _mouse );
	  _inputmanager->destroyInputObject( _keyboard );
	  OIS::InputManager::destroyInputSystem(_inputmanager);
	  _inputmanager = NULL;
	  _mouse = NULL;
	  _keyboard = NULL;
        }
    }
}

void		Application::setViewport(std::string const &name)
{
  AScene	*ptr;

  _window->removeAllViewports();

  if (_currentScene) {
    _currentScene->setVisible(false);
    _currentScene->delViewport();
    _currentScene = NULL;
  }

  _mouse->setEventCallback(NULL);
  _keyboard->setEventCallback(NULL);

  ptr = _sceneMap[name];
  ptr->setVisible(true);
  if (!ptr)
    throw graphicException("Failed to load " + name + " scene");

  ptr->createViewport();

  _mouse->setEventCallback(ptr);
  _keyboard->setEventCallback(ptr);

  _currentScene = ptr;
}

bool		Application::exec(const std::string &host, int port)
{
  if (!this->init(host, port))
    return false;

  setViewport("MenuScene");

  _root->addFrameListener(this);
  _root->startRendering();

  return true;
}

void		Application::exit()
{
  _exit = true;
}

Ogre::OverlaySystem		*Application::getOverlaySystem()
{
  return _overlaySystem;
}

OverlayImage			*Application::getMouseCursor()
{
  return _mousecursor;
}

AOverlaySceneManager		*Application::getAOverlayCursor()
{
  return _cursorOverlay;
}

Ogre::Vector2		Application::convertToWindow(unsigned int x, unsigned int y)
{
  return (Ogre::Vector2(static_cast<double>(x) / static_cast<double>(_window->getWidth()), static_cast<double>(y) / static_cast<double>(_window->getHeight())));
}
