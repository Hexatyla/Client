// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Group.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Group.hpp"

GUI::Group::Group() :  AOverlaySceneManager("Group", 10), run(false), size(0), init_d(false), officialGame(true), admin(""),
  user(" ")
{
  officialGame = true;
  vect.push_back(new Ogre::Vector2(1150, 361));
  vect.push_back(new Ogre::Vector2(1260, 361));
  vect.push_back(new Ogre::Vector2(1370, 361));
  vect.push_back(new Ogre::Vector2(1150 + 54, 258));
  vect.push_back(new Ogre::Vector2(1260 + 54, 258));
  vect.push_back(new Ogre::Vector2(1370 + 54, 258));
}

GUI::Group::~Group()
{
}

void  GUI::Group::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  winx = winX;
  winy = winY;
  BPlayer_add = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(1500, 10),
      "group_addPlayerToGame", "profil_add.png");
  title_box = this->addOverlayText(winsize, Ogre::Vector2(500, 20), Ogre::Vector2(1100, 629),
      "group_boxTitle", "bg_blue_title.png", "Conversation de groupe", true);
  InputText *txt = this->addInputText(winsize, Ogre::Vector2(500, 20), Ogre::Vector2(1100, 950),
		     "group_input", "bg_blue_input.png", "", true);
  txt->setSizeFont(16);
  txt->setSizeMax(40);
  input = txt;
  title_box->setSizeFont(16);
  box = new TextBox(_name, "box_group", "bg_blue.png", _priority, false);
  box->init("cyanBorder.png");
  box->setVisible(false); // DEBUG ERROR
  box->setSize(Ogre::Vector2(500, 300));
  box->setWindowDimensions(winsize);
  box->updatePosition(Ogre::Vector2(1100, 650));
  box->setBorders(Ogre::Vector2(5,20));
  box->setFont("MyFont");
  box->setMaxLine(20);
  // INIT scene
}

void  GUI::Group::setTypeGame(bool _act)
{
  officialGame = _act;
}

void  GUI::Group::closeGroup()
{
  box->setVisible(false);
  input->setVisible(false);
  title_box->setVisible(false);
  BPlayer_add->setVisible(false);
}

void  GUI::Group::initFct(const std::string& _name, const std::string& _admin, bool _official, GUI::TYPE_RACE r)
{
  clear();
  init_d  = true;
  officialGame = _official;
  user  = _name;
  admin = _admin;
  this->playerJoin(_name, r);
  box->setVisible(true);
  input->setVisible(true);
  title_box->setVisible(true);
  BPlayer_add->setVisible(true);
}

void  GUI::Group::clear()
{
  init_d = false;
  for (std::map<std::string, UserGroup>::iterator it = players.begin(); it != players.end(); ++it)
  {
    (players[it->first].kick)->setVisible(false);
    (players[it->first].r1)->setVisible(false);
    (players[it->first].r2)->setVisible(false);
    (players[it->first].r3)->setVisible(false);
    (players[it->first].alea)->setVisible(false);
    (players[it->first].text)->setVisible(false);
    this->delOverlay("group_race_alea_" + it->first);
    this->delOverlay("group_removePlayerToGame_" + it->first);
    this->delOverlay("group_race_1_" + it->first);
    this->delOverlay("group_race_2_" + it->first);
    this->delOverlay("group_race_3_" + it->first);
    this->delOverlay("group_name_" + it->first);
  }
  players.clear();
  for (unsigned int i = 0; i < history.size(); ++i)
  {
    delete history[i];
    history[i] = NULL;
  }
  history.clear();
  draw();
}

bool  GUI::Group::IAmAdmin()
{
  return (admin == user);
}

void  GUI::Group::playerJoin(const std::string &name, GUI::TYPE_RACE r)
{
  Ogre::Vector2 winsize(winx, winy);
  if (players.find(name) == players.end() && players.size() < 6)
  {
    players[name].race = r;
    players[name].kick = this->addButton(winsize, Ogre::Vector2(24, 28), Ogre::Vector2(0, 0),
      "group_removePlayerToGame_" + name, "delete_user_with_cross.png", false);
    players[name].kick->changeZOrder(11);
    players[name].r1 = this->addOverlayImage(winsize, Ogre::Vector2(85, 96), Ogre::Vector2(294, 159),
        "group_race_1_" + name, "race_1.png", true);
    players[name].r2 = this->addOverlayImage(winsize, Ogre::Vector2(85, 96), Ogre::Vector2(294, 159),
        "group_race_2_" + name, "race_2.png", true);
    players[name].r3 = this->addOverlayImage(winsize, Ogre::Vector2(85, 96), Ogre::Vector2(294, 159),
        "group_race_3_" + name, "race_3.png", true);
    players[name].alea = this->addOverlayImage(winsize, Ogre::Vector2(85, 96), Ogre::Vector2(294, 159),
        "group_race_alea_" + name, "race_alea.png", true);
    players[name].text = this->addOverlayText(winsize, Ogre::Vector2(100, 25), Ogre::Vector2(0, 0),
      "group_name_" + name, "empty.png", name, true);
    players[name].text->setSizeFont(16);
    size++;
  }
  else if (players.find(name) != players.end())
  {
    players[name].race = r;
  }
  draw();
}

void  GUI::Group::addPlayerToGame(const std::string& _name)
{
  if (admin == user)
  {
    // you can access at this function if you aren't admin
  }
}

void  GUI::Group::removePlayerToGame(const std::string& _name)
{
  if (admin == user)
  {
    // you can access at this function if you aren't admin
  }
}

const std::string &GUI::Group::getInput()
{
  return (input->getText());
}

void  GUI::Group::sendMessage(const std::string& _msg)
{
  input->setText("");
}

void  GUI::Group::addMessage(const std::string& _name, const std::string& _msg, unsigned int _time)
{
  ConversData *partial = new ConversData();
  if (_time == 0)
  {
    // a rempalcer par une clock
    partial->time = 0;
  }
  else
  {
    partial->time = _time;
  }
  partial->user = _name;
  partial->msg  = _msg;
  box->pushText(_name + ": " + _msg);
  history.push_back(partial);
}

void  GUI::Group::updateUser(const std::string& _name, GUI::TYPE_RACE _race, unsigned int _equip)
{
  players[_name].race = _race;
  players[_name].equip = _equip; 
  draw();
}

void  GUI::Group::deleteUser(const std::string& _name)
{
  std::map<std::string, GUI::Group::UserGroup>::iterator it = players.find(_name);

  if (it != players.end())
  {
    (players[it->first].kick)->setVisible(false);
    (players[it->first].r1)->setVisible(false);
    (players[it->first].r2)->setVisible(false);
    (players[it->first].r3)->setVisible(false);
    (players[it->first].alea)->setVisible(false);
    (players[it->first].text)->setVisible(false);
    this->delOverlay("group_race_alea_" + it->first);
    this->delOverlay("group_removePlayerToGame_" + it->first);
    this->delOverlay("group_race_1_" + it->first);
    this->delOverlay("group_race_2_" + it->first);
    this->delOverlay("group_race_3_" + it->first);
    this->delOverlay("group_name_" + it->first);
    players.erase(it);
    size--;
  }
  draw();
}

void  GUI::Group::setUser(const std::string& _user)
{
  user = _user;
}

void  GUI::Group::setAdmin(const std::string& _admin)
{
  admin = _admin;
}

void  GUI::Group::draw()
{
  unsigned int i = 0;
  std::cout << "players : empty ?" << std::endl;
  std::cout << "map size : " << players.size() << std::endl;
  for (std::map<std::string, UserGroup>::iterator it = players.begin();
        it != players.end(); ++it)
  {
    std::cout << "players : " << it->first << std::endl;
    (((it)->second).r1)->setVisible(false);
    (((it)->second).r1)->updatePosition(*(vect[i]));
    (((it)->second).r2)->setVisible(false);
    (((it)->second).r2)->updatePosition(*(vect[i]));
    (((it)->second).r3)->setVisible(false);
    (((it)->second).r3)->updatePosition(*(vect[i]));
    (((it)->second).alea)->setVisible(false);
    (((it)->second).alea)->updatePosition(*(vect[i]));
    if (((it)->second).race == GUI::R1)
      (((it)->second).r1)->setVisible(true);
    else if (((it)->second).race == GUI::R2)
      (((it)->second).r2)->setVisible(true);
    else if (((it)->second).race == GUI::R3)
      (((it)->second).r3)->setVisible(true);
    else if (((it)->second).race == GUI::ALEA)
      (((it)->second).alea)->setVisible(true);
    (((it)->second).text)->updatePosition(Ogre::Vector2((vect[i]->x), (vect[i]->y) + 
        (i < 3 ? 100 : -20)));
    (((it)->second).kick)->updatePosition(Ogre::Vector2((vect[i]->x) + 31, (vect[i]->y) + 68));
    if ((it->first) == user || admin == user)
    {
      (((it)->second).kick)->setVisible(true);
      (((it)->second).kick)->changeZOrder(11);
    }
    else
    {
      (((it)->second).kick)->setVisible(false);
      (((it)->second).kick)->changeZOrder(0);
    }
    i++;
  }
  std::cout << "end fct" << std::endl;
}
