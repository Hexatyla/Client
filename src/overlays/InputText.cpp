//
// MouseCursor.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
//
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
//
// Started on  Tue Jan 28 14:58:07 2014 Yannick Briffa
// Last update Mon Mar  3 18:07:51 2014 Yannick Briffa
//

#include	<iostream>
#include	"overlays/InputText.hh"
#include	"utils/convert.hpp"
#include	"applications/Application.hh"

InputText::InputText(std::string const &scene, std::string const &name, std::string const &file, ushort priority, bool locked, bool isPasswd)
  : OverlayText(scene, name, file, priority, locked), _cursor(0), _sizeMax(50), _characters("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "), _isPassword(isPasswd), _realText("")
{
  _specialMap[OIS::KC_UP] = &InputText::keyUp;
  _specialMap[OIS::KC_LEFT] = &InputText::keyLeft;
  _specialMap[OIS::KC_RIGHT] = &InputText::keyRight;
  _specialMap[OIS::KC_BACK] = &InputText::delChar;
  _specialMap[OIS::KC_HOME] = &InputText::setCursorBegin;
  _specialMap[OIS::KC_END] = &InputText::setCursorEnd;
}

InputText::~InputText()
{
}

bool		InputText::isPassword() const
{
  return _isPassword;
}

std::string const	&InputText::getRealText() const
{
  if (_isPassword)
    return _realText;
  else
    return (this->getText());
}

void			InputText::setText(std::string const &text)
{
  if (_isPassword) {
    _realText = text;
    _text.clear();
    _text.insert(0, text.size(), '*');
    updateText();
  }
  else
  {
    OverlayText::setText(text);
  }
}

void		InputText::focus()
{
  _cursor = _text.size();
  _text.insert(_cursor, 1, '|');
  updateText();
}

void		InputText::unfocus()
{
  _text.erase(_cursor, 1);
  updateText();
}

void		InputText::printCursor()
{
  _text.insert(_cursor, 1, '|');
}

void		InputText::unprintCursor()
{
  _text.erase(_cursor, 1);
}

void		InputText::setSizeMax(unsigned int sizeMax)
{
  _sizeMax = sizeMax;
}

unsigned int	InputText::getSizeMax()
{
  return _sizeMax;
}

//
//		VIRTUAL
//

bool		InputText::keyUp()
{
  return true;
}

bool		InputText::keyLeft()
{
  if (_cursor > 0)
    {
      unprintCursor();
      --_cursor;
      printCursor();
    }
  return true;
}

bool		InputText::keyRight()
{
  if (_cursor + 1 < _text.size())
    {
      unprintCursor();
      ++_cursor;
      printCursor();
    }
  return true;
}

bool		InputText::setCursorBegin()
{
  unprintCursor();
  _cursor = 0;
  printCursor();
  return true;
}

bool		InputText::setCursorEnd()
{
  unprintCursor();
  _cursor = _text.size();
  printCursor();
  return true;
}

bool		InputText::delChar()
{
  if (_cursor > 0 && !_text.empty())
    {
      if (_isPassword)
        _realText.erase(_cursor - 1, 1);
      _text.erase(_cursor - 1, 1);
      --_cursor;
    }
  return true;
}

bool		InputText::keyPressed(const OIS::KeyEvent &e)
{
  int		c;
  bool		ret = true;
  bool		(InputText::*ptr)();

  if (ptr = _specialMap[e.key])
    ret = (this->*ptr)();
  else if (_cursor < _sizeMax)
    {
      c = e.text;
      if (_characters.find(static_cast<char>(c)) != std::string::npos)
	{
	  if (!_isPassword)
	    _text.insert(_cursor, 1, c);
	  else {
	    _realText.insert(_cursor, 1, c);
	    _text.insert(_cursor, 1, '*');
	  }
	  ++_cursor;
	}
    }
  updateText();
  return ret;
}

bool	InputText::keyReleased(const OIS::KeyEvent &e)
{
  return true;
}


void		InputText::addValidChar(std::string const &valid)
{
  _characters += valid;
}

void		InputText::setValidChar(std::string const &valid)
{
  _characters = valid;
}
