// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/IGUI.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __IGUI_HPP__
# define  __IGUI_HPP__

namespace GUI
{
  class IGUI
  {
    public:
      virtual void draw() = 0;
  };
}

#endif /* !__IGUI_HPP__ */
