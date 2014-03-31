// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     Core.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_CORE_HPP__
# define  __GUI_CORE_HPP__

#include  "Utils/graphicException.hh"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Clock.hpp"

#include  "GUI/IGUI.hpp"

namespace GUI
{

  class Core : public IGUI, public AOverlaySceneManager
  {
    public:
    enum Type
    {
      HOME      = 0,
      ONLINE    = 1,
    };

    public:
      Core();
      ~Core();

    public:
      bool run;

    private:
      std::string     user;
      GUI::Core::Type type;
      Button          *Bprofile_add, *Bprofile_min, *Bprofile;
      Button          *Bclose, *Blaunch;
      Button          *Bspeed1, *Bspeed2, *Bspeed3, *Bteam;
      Button          *Bonline, *Bplay, *Bcampagne, *Bsetting;
      OverlayImage    *bg, *w1, *w2, *w3, *w4, *w5, *w6, *black, *time_bg;
      OverlayText     *pseudo_core, *time_text;
      Clock     time;
      bool gameStart;


    public:
      void  startGame();
      void  stopGame();
      virtual void init(unsigned int, unsigned int);
      void  setUser(std::string const&);
      const std::string &getUser();
      void  cancelGame();
      void  createGroup();
      void  moveBlackScreen(unsigned int);
      void  connectOnline();
      void  play();
      void  launch();
      void  launchSpeed3();
      void  launchSpeed2();
      void  launchSpeed1();
      void  back();
      void  setting();
      void  setType(GUI::Core::Type);
      GUI::Core::Type getType();
      virtual void draw();
      bool  gameIsStarting();
  };
}
#endif /* !__GUI_CORE_HPP__ */
