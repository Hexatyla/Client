//
// AOverlaySceneManager.cpp for PFA in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Mon Feb  3 11:04:07 2014 Yannick Briffa
// Last update Mon Mar 31 12:49:17 2014 geoffrey bauduin
//

#include	"overlays/MouseOverlayManager.hh"
#include	"Utils/graphicException.hh"

MouseOverlayManager::MouseOverlayManager()
  : AOverlaySceneManager("Mouse", 42)
{
}

MouseOverlayManager::~MouseOverlayManager()
{
}

void			  MouseOverlayManager::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2	winSize(winX, winY);
  Ogre::Vector2	size(20, 30);
  Ogre::Vector2	pos(0, 0);

  addOverlayImage(winSize, size, pos, "menuCursor", "menuCursor.png");
}
