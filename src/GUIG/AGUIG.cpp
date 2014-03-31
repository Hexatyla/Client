// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "GUIG/AGUIG.hpp"

GUIG::AGUIG::AGUIG(int x, int y) : _x(x), _y(x)
{
}

GUIG::AGUIG::~AGUIG()
{
}

void  GUIG::AGUIG::setRelatifPosition(int x, int y)
{
  _x = x;
  _y = y;
}
