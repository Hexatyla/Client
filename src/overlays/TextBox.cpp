//
// TextBox.cpp for pfa in /home/yannick/Documents/pfa/graphicClient
// 
// Made by Yannick Briffa
// Login   <yannick@epitech.net>
// 
// Started on  Thu Feb 20 11:04:42 2014 Yannick Briffa
// Last update Mon Mar 31 12:48:02 2014 geoffrey bauduin
//

#include	"overlays/TextBox.hh"
#include	"Utils/convert.hpp"

TextBox::TextBox(std::string const &scene, std::string const &name, std::string const &file, ushort priority, bool locked)
  : OverlayImage(scene, name, file, priority, locked), _textCount(0)
{
}

TextBox::~TextBox()
{
  clear();
}

void    TextBox::clear()
{
  while (!_lines.empty())
    eraseFrontText();
}

void		TextBox::init(std::string const &backfile, std::string const &font, AOverlay *parent,
			      unsigned int maxLine, unsigned int sizeFont,
			      unsigned int widthLine)
{
  _maxLine = maxLine;
  _sizeFont = sizeFont;
  _widthLine = widthLine;
  _textbgImage = backfile;

  OverlayImage::init(parent);
}


void		TextBox::setFont(std::string const &font)
{
  for (auto it : _lines)
    it->setFont(font);
  _font = font;
}

std::string const	&TextBox::getFont() const
{
  return _font;
}

void		TextBox::setSizeFont(unsigned int sizeFont)
{
  for (auto it : _lines)
    it->setSizeFont(sizeFont);
  _sizeFont = sizeFont;
}

unsigned int	TextBox::getSizeFont() const
{
  return _sizeFont;
}

void		TextBox::setMaxLine(unsigned int maxLine)
{
  _maxLine = maxLine;
}

unsigned int	TextBox::getMaxLine() const
{
  return _maxLine;
}

void		TextBox::setInterline(unsigned int interline)
{
  _interline = interline;
}

unsigned int	TextBox::getInterline() const
{
  return _interline;
}

void		TextBox::setBorders(Ogre::Vector2 const & borders)
{
  _borders = borders;
}

Ogre::Vector2 const &	TextBox::getBorders() const
{
  return _borders;
}

void		TextBox::setWidthLine(unsigned int widthLine)
{
  _widthLine = widthLine;
}

unsigned int	TextBox::getWidthLine() const
{
  return _widthLine;
}

void		TextBox::pushText(std::string const &text, Ogre::ColourValue color)
{
  if (!text.empty())
    {
      unsigned int	count;

      count = text.size() / _widthLine + 1;
      for (unsigned int i = 0 ; i < count; ++i)
	{
	  OverlayText	*ptr;
	  std::string	tmp = text.substr(i * _widthLine, _widthLine);

	  ptr = new OverlayText(_scene, "textinbox" + toString(_textCount++), "empty.png", _priority, true);
	  ptr->init(this);
	  ptr->setFont(_font);
	  ptr->setWindowDimensions(_winSize);
	  ptr->setSizeFont(_sizeFont);
	  ptr->setText(tmp);
	  ptr->setVisible(true);
	  ptr->setColor(color);
	  _lines.push_back(ptr);
	}

      while (_lines.size() > _maxLine)
	eraseFrontText();

      unsigned int i = 0;
      unsigned int begin = _size.y - _borders.y;
      unsigned int inter = (begin - _borders.y) / _maxLine;
      std::deque<OverlayText *>::iterator	it = _lines.end();

      Ogre::Vector2	pos = _borders;

      --it;
      while (_lines.empty() == false && i < _lines.size())
	{
	  std::cout << "POS TEXT BOX" << _currentPos << std::endl;
	  std::cout << "CURRENT POS" << pos + (_currentPos * _winSize) << std::endl;
	  pos.y = begin - (i + 1) * inter;
	  (*it)->updatePosition(pos + (_currentPos * _winSize));
	  --it;
	  ++i;
	}
    }
}

void		TextBox::eraseFrontText()
{
  OverlayText	*ptr;

  ptr = _lines.front();
  if (ptr)
    delete ptr;
  _lines.pop_front();
}
