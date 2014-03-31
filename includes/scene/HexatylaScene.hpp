// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/scene/Hexatyla.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef	  __HEXATYLASCENE_HH__
# define  __HEXATYLASCENE_HH__

# include	"AScene.hh"

class	HexatylaScene : public AScene
{
  private:
  bool			_moving;

  private:
    HexatylaScene();
    HexatylaScene(HexatylaScene const &);

  public:
    HexatylaScene(Ogre::RenderWindow *);
    virtual ~HexatylaScene();

  public:
    void			      moveDiag(AOverlay *);
    virtual void		createScene();
    virtual bool		keyPressed(const OIS::KeyEvent &e);
    virtual bool		keyReleased(const OIS::KeyEvent &e);
    virtual bool		mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    virtual bool		mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    virtual bool		mouseMoved(const OIS::MouseEvent &e);
};

#endif /* !__HEXATYLESCENE_HPP__ */
