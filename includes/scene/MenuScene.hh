/*
** MenuScene.h for PFA in /home/yannick/Documents/pfa/graphicClient
** 
** Made by Yannick Briffa
** Login   <yannick@epitech.net>
** 
** Started on  Sat Jan 25 14:55:33 2014 Yannick Briffa
// Last update Tue Feb 18 09:27:57 2014 Yannick Briffa
*/

#ifndef	__MENUSCENE_HH__
# define __MENUSCENE_HH__
 
# include	"AScene.hh"

class	MenuScene : public AScene
{
private:
  bool			_moving;
  MenuScene();
  MenuScene(MenuScene const &);

public:
  MenuScene(Ogre::RenderWindow *);
  virtual ~MenuScene();

  virtual void		createScene();

  void			moveDiag(AOverlay *);

  virtual bool		keyPressed(const OIS::KeyEvent &e);
  virtual bool		keyReleased(const OIS::KeyEvent &e);
  virtual bool		mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
  virtual bool		mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
  virtual bool		mouseMoved(const OIS::MouseEvent &e);
};

#endif
