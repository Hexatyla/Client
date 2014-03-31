// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Race.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_RACE_HPP__
# define  __GUI_RACE_HPP__

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  enum TYPE_RACE {
    ALEA = 0,
    R1,
    R2,
    R3
  };

  class Race : public IGUI, public AOverlaySceneManager
  {
    public:
      Race();
      ~Race();

    private:
      TYPE_RACE type;
      Button *alea;
      Button *alea_hover;
      Button *r1;
      Button *r1_hover;
      Button *r2;
      Button *r2_hover;
      Button *r3;
      Button *r3_hover;

    public:
      bool run;

    public:
      virtual void init(unsigned int, unsigned int);
      TYPE_RACE     getType();
      bool          setType(TYPE_RACE);
      virtual void  draw();
  };
}

#endif /* !__GUI_RACE_HPP__ */
