//
// Overlay.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/applications
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 14:46:25 2014 Yannick Briffa
// Last update Fri Mar 21 16:16:43 2014 gautier lefebvre
//

#ifndef __OVERLAYTEXT_HH__
# define __OVERLAYTEXT_HH__

# include	"overlays/OverlayImage.hh"

class OverlayText : public AOverlay
{
protected:
  std::string		_text;
  std::string		_backgroundFile;
  OverlayImage		*_background;
  Ogre::ColourValue	_color;
  int _paddingWith, _paddingHeight;

private:
  OverlayText();

public:
  OverlayText(std::string const &, std::string const &, std::string const & = "", ushort = 42, bool = false);
  virtual ~OverlayText();

public:
  virtual void	init(AOverlay * = NULL);
  virtual void	init(Ogre::Overlay *);
  virtual bool	isInside(unsigned int, unsigned int);

  virtual void	setPos(Ogre::Vector2 const &toCopy);

  virtual void	setSize(Ogre::Vector2 const &);
  virtual void	setWindowDimensions(Ogre::Vector2 const &);

  virtual void	setVisible(bool visible);
  virtual void	updatePosition(Ogre::Vector2 const &);

public:
  void		setOpacity(Ogre::Real);
  void		setText(std::string const &);
  void		updateText();
  virtual void		refreshPosition();
  std::string const &getText() const;

  Ogre::Vector2 const	&getTextSize();

  void		setTextPos(Ogre::Vector2 const &);
  Ogre::Vector2 const	&getTextPos() const;

  void		setColor(Ogre::ColourValue const &);
  void		setFont(std::string const &);
  void		setSizeFont(unsigned int);

  void    setPaddingWidth(int);
  void    setPaddingHeight(int);

  void		center();
};
#endif
