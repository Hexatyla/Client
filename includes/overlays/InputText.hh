//
// Overlay.hh for PFA in /home/yannick/Documents/pfa/graphicClient/includes/applications
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Tue Jan 28 14:46:25 2014 Yannick Briffa
// Last update Fri Mar 21 16:16:20 2014 gautier lefebvre
//

#ifndef __INPUTTEXT_HH__
# define __INPUTTEXT_HH__

# include	"OIS.h"
# include	"overlays/OverlayText.hh"

class InputText : public OverlayText, public OIS::KeyListener
{
protected:
  unsigned int		_cursor;
  unsigned int		_sizeMax;
  std::string		_characters;
  bool			_isPassword;
  std::string		_realText;
  std::map<OIS::KeyCode, bool (InputText::*)()>	_specialMap;

private:
  InputText();

public:
  InputText(std::string const &, std::string const &, std::string const & = "", ushort = 42, bool = false, bool = false);
  virtual ~InputText();

  bool		isPassword() const;
  std::string const	&getRealText() const;
  virtual void		setText(std::string const &);

  void		focus();
  void		unfocus();
  void		printCursor();
  void		unprintCursor();
  virtual bool	keyPressed(const OIS::KeyEvent &e);
  virtual bool	keyReleased(const OIS::KeyEvent &e);

  void		setSizeMax(unsigned int);
  unsigned int	getSizeMax();

  void		addValidChar(std::string const &);
  void		setValidChar(std::string const &);

private:
  bool		keyUp();
  bool		keyLeft();
  bool		keyRight();
  bool		delChar();
  bool		setCursorBegin();
  bool		setCursorEnd();
};
#endif
