// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Convers.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Convers.hpp"

GUI::Convers::Convers() : AOverlaySceneManager("Convers", 10), run(false), i(0), i_max(0), user_selected("")
{
}

GUI::Convers::~Convers()
{
}

void  GUI::Convers::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);
  winx = winX;
  winy = winY;

  this->addButton(winsize, Ogre::Vector2(37, 33), Ogre::Vector2(5, 1025),
      "convers_moveUp",   "arrow_left.png");
  this->addButton(winsize, Ogre::Vector2(37, 33), Ogre::Vector2(705, 1025),
      "convers_moveDown",   "arrow_right.png");

  title_box = this->addOverlayText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(50, 629),
      "convers_boxTitle", "bg_blue_title.png", "Convers : empty", true);
  txt = this->addInputText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(50, 950),
		     "convers_input", "bg_blue_input.png", "", true, true);
  close = this->addButton(winsize, Ogre::Vector2(10, 12), Ogre::Vector2(430, 631), "convers_closeBubble",
      "delete_user_with_cross.png");
  close->changeZOrder(21);
  txt->setSizeFont(16);
  txt->setSizeMax(40);
  title_box->setSizeFont(16);
  box = new TextBox(_name, "box_convers", "bg_blue.png", _priority, true);
  box->init("cyanBorder.png");
  box->setVisible(true);
  box->setSize(Ogre::Vector2(400, 300));
  box->setWindowDimensions(winsize);
  box->updatePosition(Ogre::Vector2(50, 650));
  box->setBorders(Ogre::Vector2(5,20));
  box->setFont("MyFont");
  box->setMaxLine(20);
  box->setWidthLine(65);
  insertOverlay(box->getName(), box);
  close->setVisible(false);
  txt->setVisible(false);
  box->setVisible(false);
  title_box->setVisible(false);
}

unsigned int  GUI::Convers::getUserId(const std::string& usr)
{
  return (0);
}

void  GUI::Convers::clearBox()
{
  std::cout << "Convers::clearBox::begin" << std::endl;
  box->clear();
  std::cout << "Convers::clearBox::end" << std::endl;
}

void  GUI::Convers::putConversation(const std::string &pseudo)
{
  this->clearBox();
  std::cout << "Convers::putConversation::begin" << std::endl;
  if (history.find(pseudo) == history.end())
  {
    std::cout << "Convers::putConversation::interrup" << std::endl;
    return;
  }
  for (unsigned int i = 0; i < history[user_selected].size(); ++i)
  {
    this->pushMessage(history[user_selected][i]->msg, pseudo, history[user_selected][i]->user);
    std::cout << "ECRITURE DE LA CONVERSATION msg("<< history[user_selected][i]->msg << ")" <<
     "pseudo{" << history[user_selected][i]->user << "}" << std::endl;
  }
  std::cout << "Convers::putConversation::end" << std::endl;
}

void  GUI::Convers::selectedBox(const std::string& pseudo, bool isNew)
{
  if (user_selected == pseudo)
  {
    this->closeBubble();
  }
  else
  {
    user_selected = pseudo;
    close->setVisible(true);
    txt->setVisible(true);
    box->setVisible(true);
    title_box->setVisible(true);
    title_box->setText("Convers : " + pseudo);
    putConversation(pseudo);
    if (history.find(pseudo) != history.end() && history[pseudo].size() > 0)
      history[pseudo].back()->view = false;
  }
  draw();
}

void  GUI::Convers::sendMessage(const std::string& usr, const std::string& msg)
{
  txt->setText("");
}

std::string const& GUI::Convers::getInput()
{
  return (txt->getText());
}

const std::string &GUI::Convers::getUser()
{
  return (user_selected);
}

void  GUI::Convers::pushMessage(const std::string &message, const std::string &user, bool actUser)
{
  if (message.size() <= 0)
    return;
  if (actUser)
  {
    box->pushText("me: " + message);
  }
  else
  {
    box->pushText(user + ": " + message);
  }
}

void GUI::Convers::receiveMessage(const std::string& usr, const std::string& msg, bool actUsr)
{
  unsigned int tmp;
  Conversation *partial_history = new Conversation();
  OverlayText   *text;

  partial_history->user = actUsr;
  if (user_selected == usr || actUsr)
    partial_history->view = true;
  else
    partial_history->view = false;
  partial_history->time = 0;
  partial_history->msg = msg;
  tmp = history.size();
  history[usr].push_back(partial_history);
  if (tmp != history.size())
  {
     Ogre::Vector2 winsize(winx, winy);
     std::string tmp = "";
     i_max = history.size();

     tmp = "convers_old_" + usr;
     this->addButton(winsize, Ogre::Vector2(43, 50), Ogre::Vector2(0, 0),
                      tmp, "messagerie_convers_old.png", false, true);
     tmp = "convers_new_" + usr;
     this->addButton(winsize, Ogre::Vector2(43, 50), Ogre::Vector2(0, 0),
                      tmp, "messagerie_convers_new.png", false, false);
     tmp = "convers_name_" + usr;
     text = this->addOverlayText(winsize, Ogre::Vector2(100, 25), Ogre::Vector2(0, 0),
                                  tmp, "empty.png", usr);
     text->setSizeFont(16);
     convers_order.push_back(usr);
     draw();
  }
  if (usr == user_selected)
  {
    this->pushMessage(msg, usr, actUsr);
  }
  if (user_selected == "")
    this->selectedBox(usr);
}

void  GUI::Convers::closeBubble(void)
{
  user_selected = "";
  close->setVisible(false);
  txt->setVisible(false);
  box->setVisible(false);
  title_box->setVisible(false);
  box->clear();
}

bool GUI::Convers::hiddenByPseudo(const std::string& usr)
{
}

void GUI::Convers::draw()
{
  unsigned int r = 0;
  GUI::Conversation *conv;
  while (r < convers_order.size())
  {
    const std::string &usr = convers_order[r];
    OverlayImage  *img_generic  = dynamic_cast<OverlayImage *>(getOverlay("convers_old_" + convers_order[r]));
    OverlayImage  *img_ig       = dynamic_cast<OverlayImage *>(getOverlay("convers_new_" + convers_order[r]));
    OverlayText   *pseudo       = dynamic_cast<OverlayText *>(getOverlay("convers_name_" + convers_order[r]));

    if (r < 11)
    {
      if (!(history[usr].size() > 0 && (history[usr].back())->view == false))
      {
        img_ig->setVisible(true);
        pseudo->setVisible(true);
        img_ig->updatePosition(Ogre::Vector2(40 + 61 * r, 1005));
        pseudo->updatePosition(Ogre::Vector2(44 + 61 * r, 1060));
        img_generic->setVisible(false);
      }
      else
      {
        pseudo->setVisible(true);
        img_generic->setVisible(true);
        img_generic->updatePosition(Ogre::Vector2(40 + 61 * r, 1005));
        pseudo->updatePosition(Ogre::Vector2(44 + 61 * r, 1060));
        img_ig->setVisible(false);
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
  this->putConversation(user_selected);
}

void GUI::Convers::moveUp()
{
  if (convers_order.size() > 11)
  {
    i++;
    if (i >= i_max)
      i = 0;
    convers_order.push_back(convers_order.front());
    convers_order.pop_front();
    draw();
  }
}

void  GUI::Convers::moveDown()
{
  if (convers_order.size() > 11)
  {
    i--;
    if (i < 0)
    {
      if (i_max == 0)
        i = i_max;
      else
        i = i_max - 1;
    }
    convers_order.push_front(convers_order.back());
    convers_order.pop_back();
    draw();
  }
}
