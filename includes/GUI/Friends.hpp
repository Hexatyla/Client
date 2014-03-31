// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Friends.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_FRIENDS_HPP__
# define  __GUI_FRIENDS_HPP__

#include  <map>
#include  <string>
#include  <deque>
#include  "GUI/IGUI.hpp"
#include  "overlays/AOverlaySceneManager.hh"

namespace GUI
{
  namespace Activity {
    enum Player {
      ON    = 0,
      OFF   = 1,
      AWAY  = 2,
      IGAME = 3
    };
  }

  class Friends : public IGUI, public AOverlaySceneManager
  {
    public:
      Friends();
      ~Friends();

    public:
      bool run;

    private:
      unsigned int winx, winy;
      int i;
      int i_max;
      std::map<std::string, GUI::Activity::Player> friends;
      std::deque<std::string> friends_order;

    public:
      virtual void init(unsigned int, unsigned int);
      void  infoFriend(std::string const&, GUI::Activity::Player stat = GUI::Activity::OFF);
      void  rmFriend(std::string const&);
      void  addFriend(std::string const&);
      void  moveUp();
      void  moveDown();
      virtual void draw();
  };
}

#endif /* !__GUI_FRIENDS_HPP__ */
