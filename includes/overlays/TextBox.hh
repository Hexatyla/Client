//
// BoxText.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/overlays
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Thu Feb 20 10:32:57 2014 Yannick Briffa
// Last update Thu Mar 20 18:15:28 2014 gautier lefebvre
//

#ifndef __TEXTBOX_HH__
# define __TEXTBOX_HH__

# include	"overlays/OverlayImage.hh"
# include	"overlays/OverlayText.hh"

class	TextBox : public OverlayImage
{
  unsigned int			_textCount;
  std::string			_textbgImage;
  unsigned int			_maxLine;
  unsigned int			_sizeFont;
  unsigned int			_widthLine;
  std::string			_font;
  std::deque<OverlayText *>	_lines;
  unsigned int			_interline;
  Ogre::Vector2			_borders;

public:
  TextBox(std::string const &, std::string const &, std::string const &, ushort, bool = false);
  virtual ~TextBox();

  void		init(std::string const &, std::string const & = "BerlinSans32", AOverlay * = NULL, unsigned int = 10, unsigned int = 15, unsigned int = 50);

public:
  void		setFont(std::string const &);
  std::string const	&getFont() const;

  void		setSizeFont(unsigned int);
  unsigned int	getSizeFont() const;

  void		setMaxLine(unsigned int);
  unsigned int	getMaxLine() const;

  void    clear();
  void		setInterline(unsigned int);
  unsigned int	getInterline() const;

  void		setBorders(Ogre::Vector2 const &);
  Ogre::Vector2 const &getBorders() const;

  void		setWidthLine(unsigned int);
  unsigned int	getWidthLine() const;

  void		pushText(std::string const &, Ogre::ColourValue = Ogre::ColourValue(1.0, 1.0, 1.0));

  void		eraseFrontText();
};


#endif
