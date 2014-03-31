// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Tooltip.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_TOOLTIP_HPP__
# define  __GUI_TOOLTIP_HPP__

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class Tooltip : public IGUI, public AOverlaySceneManager
  {
    public:
      Tooltip();
      virtual ~Tooltip();

    public:
      bool run;

    public:
      virtual void init(unsigned int, unsigned int);
      virtual void draw();
  };
}

#endif  /* !__GUI_TOOLTIP_HPP__ */
