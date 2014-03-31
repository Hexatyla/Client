//
// AScene.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sat Jan 25 14:15:12 2014 Yannick Briffa
// Last update Wed Mar 12 14:53:17 2014 Yannick Briffa
//

#include	<stdio.h>

#include	<iterator>
#include	"scene/AScene.hh"
#include	"CEGUI/CEGUI.h"
#include	"CEGUI/RendererModules/Ogre/Renderer.h"
#include	"applications/Application.hh"

AScene::AScene(std::string const &name, Ogre::RenderWindow *window, Ogre::ColourValue const &background)
  : _name(name), _window(window), _sceneMgr(NULL), _camera(NULL), _viewport(NULL), _background(background), _currentInput(NULL), _currentOn(NULL), _currentClick(NULL), _raySceneQuery(NULL), _leftClickDown(false), _rightClickDown(false), _objectClick(NULL)
{
}

AScene::~AScene()
{
  if (_raySceneQuery)
    _sceneMgr->destroyQuery(_raySceneQuery);
}

void		AScene::init(Ogre::Root *root)
{
  if (!(_sceneMgr = root->createSceneManager(Ogre::ST_GENERIC, _name + "_SceneManager")))
    throw graphicException("can't create " + _name +  " sceneManager");
  createCamera();
  createScene();

  _sceneMgr->addRenderQueueListener(Application::getInstance()->getOverlaySystem());

  _raySceneQuery = _sceneMgr->createRayQuery(Ogre::Ray());
}

void		AScene::createCamera()
{
  _camera = _sceneMgr->createCamera(_name + "Cam");
  _camera->setPosition(Ogre::Vector3(0,0,100));
  _camera->lookAt(Ogre::Vector3(0,0,0));
  _camera->setNearClipDistance(5);
}

void		AScene::createViewport()
{
  if (!(_viewport = _window->addViewport(_camera)))
    throw graphicException("failed to create Viewport");
  _viewport->setBackgroundColour(_background);
  _camera->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) / Ogre::Real(_viewport->getActualHeight()));
}


std::string const	&AScene::getName() const
{
  return _name;
}

void			AScene::delViewport()
{
  _viewport = NULL;
}

Ogre::ColourValue const	&AScene::getBackgroundColor() const
{
  return _background;
}

bool			AScene::updateFrame(const Ogre::FrameEvent &evt)
{
  bool ret = true;

  for (auto it : _listMove)
    ret = ((it)->update(evt) == false ? false : ret);
  clearListMove();
  return (true);
}

bool			AScene::mouseMoved(const OIS::MouseEvent &evt)
{
  AOverlay		*ptr = Application::getInstance()->getMouseCursor();

  if (ptr)
    ptr->updatePosition(Ogre::Vector2(evt.state.X.abs, evt.state.Y.abs));
}

void			AScene::addEffect(IEffect *move)
{
  if (move)
    _listMove.push_back(move);
}

AOverlaySceneManager	*AScene::getOverlaySceneManager(std::string const &name)
{
  if (_overlayManagerMap.size() < 1)
    throw graphicException("Fucked up, no overlay manager in this scene");
  return _overlayManagerMap[name];
}

void			AScene::pickFirstObject3DOnClick(const OIS::MouseEvent &e)
{
  Ogre::Ray mouseRay = _camera->getCameraToViewportRay(e.state.X.abs / (float)_window->getWidth(), (e.state.Y.abs / (float)_window->getHeight()));

  _raySceneQuery->clearResults();
  _raySceneQuery->setRay(mouseRay);
  _raySceneQuery->setSortByDistance(true);
  _raySceneQuery->execute();

  Ogre::RaySceneQueryResult &result = _raySceneQuery->getLastResults();
  Ogre::RaySceneQueryResult::iterator itr = result.begin();

  _objectClick = NULL;
  if (itr != result.end() && itr->movable)
  {
      _objectClick = dynamic_cast<Ogre::Entity *>(itr->movable);
      std::cout << _objectClick->getName() << " : filefjeifeoj" << std::endl;
  }
}

void			AScene::clearListMove()
{
  std::list<IEffect *>::iterator it = _listMove.begin();
  std::list<IEffect *>::iterator itsave;

  while (it != _listMove.end())
    {
      if (*it == NULL || (*it)->isEnded())
	{
	  if (*it)
	    delete *it;
	  if (it == _listMove.begin())
	    {
	      _listMove.erase(it);
	      it = _listMove.begin();
	      if (_listMove.empty())
		break;
	    }
	  else
	    {
	      _listMove.erase(it);
	      it = itsave;
	    }
	}
      itsave = it;
      ++it;
    }
}

void		AScene::subscribe(AOverlay *overlay, bool (*ptrfunc)(AScene *, AOverlay *))
{
  _subscribed[overlay] = ptrfunc;
}

bool		AScene::executeSubscribe(AOverlay *overlay)
{
  if (!_subscribed.empty())
    {
      bool		(*tmp)(AScene *, AOverlay *) = _subscribed[overlay];

      if (!tmp)
	return false;
      return (tmp(this, overlay));
    }
  return false;
}

void    AScene::setVisible(bool v)
{
  if (v == false)
  {
    for (std::map<std::string, AOverlaySceneManager *>::iterator it = _overlayManagerMap.begin();
          it != _overlayManagerMap.end(); ++it)
    {
      _overlayManagerMapv[it->first] = (it->second)->isVisible();
      _overlayManagerMap[it->first]->setVisible(false);
    }
  }
  else
  {
    for (std::map<std::string, bool>::iterator it = _overlayManagerMapv.begin();
          it != _overlayManagerMapv.end(); ++it)
    {
      _overlayManagerMap[it->first]->setVisible(it->second);
    }
  }
}

void		AScene::deleteOverlayWithEffect(AOverlay *ptr)
{
  for (std::list<IEffect *>::iterator it = _listMove.begin(); it != _listMove.end();)
    {
      if ((*it)->getObject() == ptr)
	{
	  delete (*it);
	  it = _listMove.erase(it);
	}
      else
	++it;
    }
}
