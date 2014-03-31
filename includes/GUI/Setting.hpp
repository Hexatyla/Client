// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/Map/Alignment.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_SETTING_HPP__
# define  __GUI_SETTING_HPP__

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class Setting : public IGUI, public AOverlaySceneManager
  {
    public:
      Setting();
      ~Setting();

    public:
      bool run;

    public:
      virtual void init(unsigned int, unsigned int);
      void  exit();
      virtual void draw();
  };
}

#endif /* !__GUI_SETTING_HPP__ */
