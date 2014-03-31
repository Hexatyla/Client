// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __AGUIG_HPP__
# define  __AGUIG_HPP__

// Graphical User Interface Game
namespace GUIG
{
  // Abstract GUIG
  class AGUIG
  {
    public:
      int _x;
      int _y;

    public:
      AGUIG(int x = 0, int y = 0);
      ~AGUIG();

    public:
      void  setRelatifPosition(int x, int y);
      virtual void draw() = 0;
  };
}

#endif /* !__IGUIG_HPP */
