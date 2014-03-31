//
// MenuScene.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sat Jan 25 15:22:38 2014 Yannick Briffa
// Last update Thu Feb 20 13:10:10 2014 Yannick Briffa
//

#include	<algorithm>
#include	"scene/HexatylaScene.hh"
#include	"applications/Application.hh"
#include	"effects/MoveOverlay.hh"
#include	"effects/MoveObject.hh"
#include	"effects/Scale.hh"
#include	"effects/Fade.hh"
#include	"overlays/MainHexatyla.hpp"
#include	"overlays/Click.hh"

HexatylaScene::HexatylaScene(Ogre::RenderWindow *win)
  : AScene(std::string("MenuScene"), win, Ogre::ColourValue(0.08,0.08,0.08)), _moving(false)
{
}

HexatylaScene::~HexatylaScene()
{
}

static bool	launchMoveDiag(AScene *scene, AOverlay *overlay)
{
  HexatylaScene	*ptr = dynamic_cast<HexatylaScene *>(scene);

  if (!ptr)
    return false;
  ptr->moveDiag(overlay);
  return true;
}

void		HexatylaScene::moveDiag(AOverlay *overlay)
{
  std::pair<double,double>	toto(0.4, 0.4);
  std::pair<double,double>	titi(1.0, 1.0);

  addEffect(new Fade(dynamic_cast<OverlayImage *>(overlay), 0.8, 0.3, 3));
}

void		HexatylaScene::createScene()
{
  _sceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.8));

  _overlayManager = new MainHexatyla();
  _overlayManager->init(_window->getWidth(), _window->getHeight());

  _currentInput = dynamic_cast<InputText *>(_overlayManager->getOverlay("imageMenu1"));
}

bool HexatylaScene::keyPressed( const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
    Application::getInstance()->exit();
  else if (e.key == OIS::KC_F1)
    _overlayManager->setVisible(true);
  else if (e.key == OIS::KC_F2)
    _overlayManager->setVisible(false);
  else if (_currentInput && !_currentInput->keyPressed(e))
    _currentInput = NULL;
}

bool	HexatylaScene::keyReleased(const OIS::KeyEvent &e)
{
  if (_currentInput && !_currentInput->keyReleased(e))
    _currentInput = NULL;
}

bool	HexatyalaScene::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  pickFirstObject3DOnClick(e);
  if (_overlayManager)
    {
      std::vector<AOverlay *>	ptr = _overlayManager->getOverlayAt(e.state.X.abs, e.state.Y.abs);

      for (auto it : ptr)
	    {
        if (IClick *tmp = dynamic_cast<IClick *>(it))
          if (!it->isLocked() && it->isInside(e.state.X.abs, e.state.Y.abs))
            addEffect(tmp->effectOnClick());
	      executeSubscribe(it);
	    }
    }
  _moving = !_listMove.empty();
  return true;
}

bool	HexatylaScene::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
  return true;
}

bool	HexatylaScene::mouseMoved(const OIS::MouseEvent &e)
{
  if (_overlayManager)
    {
      std::vector<AOverlay *>	ptr = _overlayManager->getOverlayAt(e.state.X.abs, e.state.Y.abs);

      if (ptr.size() != 1 && _currentOn) {
	_currentOn->reinitZOrder();
	_currentOn = NULL;
      }
      else if (ptr.size() == 1) {
	if (_currentOn && _currentOn != ptr.front())
	  _currentOn->reinitZOrder();
	if (!ptr.front()->isLocked())
	  {
	    _currentOn = ptr.front();
	    _currentOn->changeZOrder(2);
	  }
      }
    }
  return (AScene::mouseMoved(e));
}
