//
// MenuScene.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Sat Jan 25 15:22:38 2014 Yannick Briffa
// Last update Thu Feb 20 15:26:40 2014 Yannick Briffa
//

#include	<algorithm>
#include  <map>
#include	"scene/MenuScene.hh"
#include	"applications/Application.hh"
#include	"effects/MoveOverlay.hh"
#include	"effects/MoveObject.hh"
#include	"effects/Scale.hh"
#include	"effects/Fade.hh"
#include	"overlays/MainMenuOverlaySceneManager.hh"
#include	"overlays/Click.hh"
#include	"overlays/TextBox.hh"
#include	"utils/convert.hpp"

MenuScene::MenuScene(Ogre::RenderWindow *win)
  : AScene(std::string("MenuScene"), win, Ogre::ColourValue(0.08,0.08,0.08)), _moving(false)
{
}

MenuScene::~MenuScene()
{
}

static bool	launchMoveDiag(AScene *scene, AOverlay *overlay)
{
  MenuScene	*ptr = dynamic_cast<MenuScene *>(scene);

  if (!ptr)
    return false;
  ptr->moveDiag(overlay);
  return true;
}

void		MenuScene::moveDiag(AOverlay *overlay)
{
  std::pair<double,double>	toto(0.4, 0.4);
  std::pair<double,double>	titi(1.0, 1.0);

  addEffect(new Fade(dynamic_cast<OverlayImage *>(overlay), 0.8, 0.3, 3));
}

void		MenuScene::createScene()
{
  _sceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.8));

  _overlayManagerMap["scene"] = new MainMenuOverlaySceneManager();
  _overlayManagerMap["scene"]->init(_window->getWidth(), _window->getHeight());

  _currentInput = dynamic_cast<InputText *>(_overlayManagerMap["scene"]->getOverlay("imageMenu1"));
}

bool MenuScene::keyPressed( const OIS::KeyEvent &e)
{
  static unsigned int i = 0;

  if (e.key == OIS::KC_ESCAPE)
    Application::getInstance()->exit();
  else if (e.key == OIS::KC_F1)
    _overlayManagerMap["scene"]->setVisible(true);
  else if (e.key == OIS::KC_F2)
    _overlayManagerMap["scene"]->setVisible(false);
  else if (e.key == OIS::KC_F3)
    {
      TextBox *tmp = dynamic_cast<TextBox *>(_overlayManagerMap["scene"]->getOverlay("TestTextBox"));
      tmp->pushText("TA MERE PETE A TABLE " + toString(i++));
    }
  else if (e.key == OIS::KC_F4)
    {
      static bool size = false;
      TextBox *tmp = dynamic_cast<TextBox *>(_overlayManagerMap["scene"]->getOverlay("TestTextBox"));

      tmp->setSizeFont(size ? 15 : 30);
      size = !size;
    }
  else if (e.key == OIS::KC_F5)
    {
      static bool		font = false;;
      TextBox *tmp = dynamic_cast<TextBox *>(_overlayManagerMap["scene"]->getOverlay("TestTextBox"));

      std::cout << "ça change la font en : " << (font ? "BerlinSans32" : "MyFont")<< std::endl;
      tmp->setFont(font ? "BerlinSans32" : "MyFont");
      font = !font;
    }
  else if (_currentInput && !_currentInput->keyPressed(e))
    _currentInput = NULL;
  return true;
}

bool	MenuScene::keyReleased(const OIS::KeyEvent &e)
{
  if (_currentInput && !_currentInput->keyReleased(e))
    _currentInput = NULL;
  return true;
}

bool	MenuScene::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  pickFirstObject3DOnClick(e);

  if (_overlayManagerMap["scene"])
    {
      std::vector<AOverlay *>	ptr = _overlayManagerMap["scene"]->getOverlayAt(e.state.X.abs, e.state.Y.abs);

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

bool	MenuScene::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
  return true;
}

bool	MenuScene::mouseMoved(const OIS::MouseEvent &e)
{
  if (_overlayManagerMap["scene"])
    {
      std::vector<AOverlay *>	ptr = _overlayManagerMap["scene"]->getOverlayAt(e.state.X.abs, e.state.Y.abs);

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
