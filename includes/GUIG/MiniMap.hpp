// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __MINIMAP_HPP__
# define  __MINIMAP_HPP__

# include  "GUIG/AGUIG.hpp"
# include  "overlays/AOverlaySceneManager.hh"
# include  "overlays/Button.hh"
# include  "overlays/OverlayText.hh"

namespace GUIG
{
  #define	MAXSCROLL	2
  #define	MINSCROLL	0

  class Minimap: public AGUIG, public AOverlaySceneManager
  {
  private:
    Ogre::Vector2	_size;
    Ogre::Vector2	_lookPos;
    unsigned int	_currentScroll;
    Ogre::Overlay	*_mainOverlay;
    OverlayImage	*_border;
    OverlayImage	*_minimap;
    OverlayImage	*_borderLook;
    Button		*_plus;
    Button		*_minus;
    Ogre::Vector2	_borderLookSize[3];

  public:
    Minimap(ushort prio, Ogre::Vector2 const &size);
    ~Minimap();

    void	init(unsigned int, unsigned int);
    void	draw();

    Minimap	&operator++(int);
    Minimap	&operator--(int);

    Button	*getPlusButton();
    Button	*getMinusButton();

    bool  canScrollUp();
    bool  canScrollDown();
    const Ogre::Vector2 &getPosition();
    const Ogre::Vector2 &getLookPosition() const;
    const Ogre::Vector2 &getSize() const;
    void	moveLook(Ogre::Vector2 const &centerLooked);
 };
}

#endif  /* ___HPP__ */
