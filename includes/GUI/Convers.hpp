// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     Concers.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_CONVER_HPP__
# define  __GUI_CONVER_HPP__

#include  <string>
#include  <vector>
#include  <map>
#include  <deque>

#include	"overlays/TextBox.hh"
#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI {
  namespace EnumConvers {
    enum  Stat {
      HIDDEN = 0,
      VISIBLE,
      NEW
    };
  }
}

namespace GUI
{
  struct Conversation {
    bool  user;
    bool  view;
    int   time;
    std::string msg;
  };

  class Convers : public IGUI, public AOverlaySceneManager
  {
    public:
      Convers();
      ~Convers();

    public:
      bool run;

    private:
      Button  *close;
      InputText *txt;
      TextBox *box;
      OverlayText *title_box;
      unsigned int winx, winy;
      int i;
      int i_max;
      std::string user_selected;
      std::map<std::string, std::vector<GUI::Conversation*>> history;
      std::deque<std::string> convers_order;

    private:
      void  clearBox();
      void  pushMessage(const std::string &message, const std::string &user, bool actUser);
      void  putConversation(const std::string&);

    public:
      virtual void init(unsigned int, unsigned int);
      std::string const& getInput();
      std::string const& getUser();
      void  sendMessage(const std::string&, const std::string&);
      void  receiveMessage(const std::string&, const std::string&, bool actUsr = true);
      void  selectedBox(const std::string&, bool = false);
      void  closeBubble(void);
      bool  hiddenByPseudo(const std::string&);
      virtual void draw();
      void  moveUp();
      void  moveDown();

    private:
      unsigned int getUserId(const std::string&);
  };
}

#endif /* !__GUI_CONVERS_HPP__ */
