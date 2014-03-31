// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Friends.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Friends.hpp"

GUI::Friends::Friends() : AOverlaySceneManager("Friends", 10), run(false), i(0), i_max(0)
{
}

GUI::Friends::~Friends()
{
}

void  GUI::Friends::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);
  winx = winX;
  winy = winY;

  this->addButton(winsize, Ogre::Vector2(33, 37), Ogre::Vector2(1790, 45),
      "friends_moveUp",   "arrow_top.png");
  this->addButton(winsize, Ogre::Vector2(33, 37), Ogre::Vector2(1790, 990),
      "friends_moveDown",   "arrow_bottom.png");
}

void  GUI::Friends::infoFriend(std::string const& usr, GUI::Activity::Player stat)
{
  friends[usr] = stat;

  if (i_max != friends.size())
  {
    Ogre::Vector2 winsize(winx, winy);
    OverlayText   *text;
    std::string tmp = "";
    i_max = friends.size();

    tmp = "friends_mess_" + usr;
    this->addButton(winsize, Ogre::Vector2(43, 50), Ogre::Vector2(0, 0),
      tmp, "messagerie_convers_old.png", false, true);
    tmp = "friends_ingame_" + usr;
    this->addButton(winsize, Ogre::Vector2(43, 50), Ogre::Vector2(0, 0),
      tmp, "messagerie_convers_ingame.png", false, false);
    tmp = "friends_offline_" + usr;
    this->addButton(winsize, Ogre::Vector2(43, 50), Ogre::Vector2(0, 0),
      tmp, "messagerie_convers_hl.png", false, false);
    tmp = "friends_name_" + usr;
    text = this->addOverlayText(winsize, Ogre::Vector2(100, 25), Ogre::Vector2(0, 0),
      tmp, "empty.png", usr);
    text->setSizeFont(18);
    friends_order.push_back(usr);
  }
  draw();
}

void  GUI::Friends::rmFriend(std::string const& usr)
{
  std::map<std::string, GUI::Activity::Player>::iterator it = friends.find(usr);

  if (it != friends.end())
  {
    friends.erase(it);
    i_max -= 1;
    if (i >= i_max)
      i = 0;
    unsigned r = 0;
    for (unsigned i = 0; i < friends_order.size(); ++i)
      if (friends_order[i] == usr)
      {
        r = i;
        OverlayImage  *img_generic  = dynamic_cast<Button*>(getOverlay("friends_mess_" + friends_order[r]));
        OverlayImage  *img_ig       = dynamic_cast<Button*>(getOverlay("friends_ingame_" + friends_order[r]));
        OverlayImage  *img_off      = dynamic_cast<Button*>(getOverlay("friends_offline_" + friends_order[r]));
        OverlayText   *pseudo       = dynamic_cast<OverlayText *>(getOverlay("friends_name_" + friends_order[r]));
        img_generic->setVisible(false);
        img_ig->setVisible(false);
        img_off->setVisible(false);
        pseudo->setVisible(false);
        this->delOverlay("friends_mess_" + friends_order[r]);
        this->delOverlay("friends_ingame_" + friends_order[r]);
        this->delOverlay("friends_offline_" + friends_order[r]);
        this->delOverlay("friends_name_" + friends_order[r]);
        break;
      }
    if (r < friends_order.size())
      friends_order.erase(friends_order.begin() + r);
    draw();
  }
}

void  GUI::Friends::addFriend(std::string const& usr)
{
  /// USERLESS
}

void GUI::Friends::draw()
{
  unsigned int r = 0;
  while (r < friends_order.size())
  {
    OverlayImage  *img_generic  = dynamic_cast<OverlayImage *>(getOverlay("friends_mess_" + friends_order[r]));
    OverlayImage  *img_ig       = dynamic_cast<OverlayImage *>(getOverlay("friends_ingame_" + friends_order[r]));
    OverlayImage  *img_off      = dynamic_cast<OverlayImage *>(getOverlay("friends_offline_" + friends_order[r]));
    OverlayText   *pseudo       = dynamic_cast<OverlayText *>(getOverlay("friends_name_" + friends_order[r]));

    if (r < 11)
    {
      if (friends[friends_order[r]] == GUI::Activity::IGAME)
      {
        img_ig->setVisible(true);
        pseudo->setVisible(true);
        img_ig->updatePosition(Ogre::Vector2(1788, 90 + 80 * r));
        pseudo->updatePosition(Ogre::Vector2(1788, 145 + 80 * r));
        img_generic->setVisible(false);
        img_off->setVisible(false);
      }
      else if (friends[friends_order[r]] == GUI::Activity::OFF)
      {
        pseudo->setVisible(true);
        img_off->setVisible(true);
        img_off->updatePosition(Ogre::Vector2(1788, 90 + 80 * r));
        pseudo->updatePosition(Ogre::Vector2(1788, 145 + 80 * r));
        img_ig->setVisible(false);
        img_generic->setVisible(false);
      }
      else
      {
        pseudo->setVisible(true);
        img_generic->setVisible(true);
        img_generic->updatePosition(Ogre::Vector2(1788, 90 + 80 * r));
        pseudo->updatePosition(Ogre::Vector2(1788, 145 + 80 * r));
        img_ig->setVisible(false);
        img_off->setVisible(false);
      }
    }
    else
    {
      img_generic->setVisible(false);
      img_ig->setVisible(false);
      pseudo->setVisible(false);
    }
    r += 1;
  }
}

void GUI::Friends::moveUp()
{
  if (friends_order.size() > 10)
  {
    i++;
    if (i >= i_max)
      i = 0;
    friends_order.push_back(friends_order.front());
    friends_order.pop_front();
    draw();
  }
}

void  GUI::Friends::moveDown()
{
  if (friends_order.size() > 10)
  {
    i--;
    if (i < 0)
    {
      if (i_max == 0)
        i = i_max;
      else
        i = i_max - 1;
    }
    friends_order.push_front(friends_order.back());
    friends_order.pop_back();
    draw();
  }
}
