// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Group.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_GROUP_HPP__
# define  __GUI_GROUP_HPP__

#include  <string>
#include  <vector>
#include  <map>

#include  "overlays/AOverlaySceneManager.hh"
#include	"overlays/TextBox.hh"
#include  "GUI/IGUI.hpp"
#include  "GUI/Race.hpp"

namespace GUI
{
  class Group : public IGUI, public AOverlaySceneManager
  {
    struct UserGroup
    {
      GUI::TYPE_RACE  race;
      unsigned int    equip;
      OverlayImage    *r1;
      OverlayImage    *r2;
      OverlayImage    *r3;
      OverlayImage    *alea;
      OverlayText     *text;
      Button          *kick;
    };

    struct ConversData
    {
      std::string user;
      std::string msg;
      unsigned int time;
    };

    public:
      Group();
      ~Group();

    public:
      bool run;
      unsigned int size;

    private:
      InputText *input;
      TextBox *box;
      OverlayText *title_box;
      Button  *BPlayer_add;
      unsigned int winx, winy;
      bool init_d;
      bool officialGame;
      std::string admin;
      std::string user;
      std::map<std::string, UserGroup> players;
      std::vector<ConversData*> history;
      std::vector<Ogre::Vector2*> vect;


    public:
      virtual void init(unsigned int, unsigned int);
      void  initFct(const std::string&, const std::string&, bool _official = true, GUI::TYPE_RACE r = GUI::ALEA);
      void  clear();
      void  playerJoin(const std::string&, GUI::TYPE_RACE);
      const std::string& getInput();
      void  addPlayerToGame(const std::string&);
      void  removePlayerToGame(const std::string&);
      void  sendMessage(const std::string&);
      void  addMessage(const std::string&, const std::string&, unsigned int);
      void  updateUser(const std::string&, GUI::TYPE_RACE, unsigned int equipe = 0);
      void  deleteUser(const std::string&);
      void  closeGroup();
      void  setTypeGame(bool);
      void  setUser(const std::string&);
      void  setAdmin(const std::string&);
      bool  IAmAdmin();
      virtual void draw();
  };
}

#endif /* !__GUI_GROUP_HPP__ */
