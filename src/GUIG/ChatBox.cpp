//
// ChatBox.cpp for pfa
// 
// Made by gautier lefebvre
// 
// Started on  Thu Mar 20 16:08:23 2014 gautier lefebvre
// Last update Sat Mar 22 13:14:06 2014 gautier lefebvre
//

#include	"GUIG/ChatBox.hpp"
#include	"Network/Manager/Client.hpp"
#include	"Factory/Protocol.hpp"
#include	"Logger.hpp"

GUIG::ChatBox::Message::Message():
  type(GUIG::ChatBox::Message::ALL),
  from(""),
  msg(""),
  time(0)
{}

GUIG::ChatBox::Message::Message(GUIG::ChatBox::Message::Type t, const std::string &from, const std::string &msg, unsigned int time):
  type(t),
  from(from),
  msg(msg),
  time(time)
{}

GUIG::ChatBox::Message::Message(const GUIG::ChatBox::Message &oth):
  type(oth.type),
  from(oth.from),
  msg(oth.msg),
  time(oth.time)
{}

GUIG::ChatBox::Message&	GUIG::ChatBox::Message::operator=(const GUIG::ChatBox::Message &oth)
{
  if (this != &oth) {
    this->type = oth.type;
    this->from = oth.from;
    this->msg = oth.msg;
    this->time = oth.time;
  }
  return (*this);
}

GUIG::ChatBox::Message::~Message() {}

GUIG::ChatBox::ChatBox():
  AOverlaySceneManager("GUIG_ChatBox", 10),
  _msgs(),
  _input(NULL),
  _box(NULL),
  _winsize()
{}

GUIG::ChatBox::~ChatBox() {}

void	GUIG::ChatBox::draw() {
}

void	GUIG::ChatBox::init(unsigned int wx, unsigned int wy) {
  this->_winsize = Ogre::Vector2(wx, wy);

  this->_input = this->addInputText(this->_winsize, Ogre::Vector2(500, 20), Ogre::Vector2(_x, 300 + _y), "guigChatbox_input", "bg_blue_input.png", "", true);
  this->_input->setSizeMax(40);
  this->_input->setSizeFont(16);
  this->_input->setVisible(true);
  this->_input->setOpacity(0.5);

  this->_box = new TextBox(_name, "guig_textbox", "bg_blue.png", _priority, false);
  this->_box->init("cyanBorder.png");
  this->_box->setSize(Ogre::Vector2(500, 300));
  this->_box->setWindowDimensions(this->_winsize);
  this->_box->updatePosition(Ogre::Vector2(_x, _y));
  this->_box->setBorders(Ogre::Vector2(5, 20));
  this->_box->setFont("MyFont");
  this->_box->setMaxLine(20);
  this->_box->setOpacity(0.5);
  this->_box->setVisible(false);
  this->_input->addValidChar("/");
}

void	GUIG::ChatBox::clear() {
  
}

void	GUIG::ChatBox::enterGame() {
  this->_box->setVisible(true);
  draw();
}

void	GUIG::ChatBox::leaveGame() {
  this->_box->setVisible(false);
  draw();
}

void	GUIG::ChatBox::recvWhisp(const std::string &from, const std::string &msg) {
  this->_msgs.push_back(GUIG::ChatBox::Message(GUIG::ChatBox::Message::PRIVATE, from, msg, 0));
  this->_box->pushText(from + ": " + msg, Ogre::ColourValue(0.92, 1.00, 0.71));
}

void	GUIG::ChatBox::recvGrpMsg(const std::string &from, const std::string &msg) {
  this->_msgs.push_back(GUIG::ChatBox::Message(GUIG::ChatBox::Message::GROUP, from, msg, 0));
  this->_box->pushText(from + ": " + msg, Ogre::ColourValue(1.0, 105.0 / 255.0, 180.0 / 255.0));
}

void	GUIG::ChatBox::recvMsgGlob(const std::string &from, const std::string &msg) {
  this->_msgs.push_back(GUIG::ChatBox::Message(GUIG::ChatBox::Message::ALL, from, msg, 0));
  this->_box->pushText(from + ": " + msg);
}

void	GUIG::ChatBox::sendMsg() {
  std::string msg = this->getInput();
  this->_input->setText("");

  if (msg.length() > 3 && msg.substr(0, 3) == "/w ") {
    this->sendWhisp(msg);
  }
  else if (msg.length() > 3 && msg.substr(0, 3) == "/g ") {
    this->sendMsgGrp(msg);
  }
  else if (msg != "") {
    this->sendMsgGlob(msg);
  }
}

const std::string &GUIG::ChatBox::getInput() {
  return (this->_input->getText());
}

void	GUIG::ChatBox::sendWhisp(const std::string &str) {
  std::string to;
  std::string msg;
  std::string tmp = str.substr(2);

  size_t pos;
  size_t l = tmp.length();
  for (pos = 0 ; tmp.length() > pos ; ++pos) {
    if (tmp[pos] != ' ') {
      tmp = tmp.substr(pos);
      break ;
    }
  }
  pos = tmp.find_first_of(" ");
  if (pos == std::string::npos) { return ; }
  to = tmp.substr(0, pos);
  msg = tmp.substr(pos);
  if (msg.find_first_not_of(" ") == std::string::npos) { return ; }

  for (pos = 0 ; msg.length() > pos ; ++pos) {
    if (msg[pos] != ' ') {
      msg = msg.substr(pos);
      break ;
    }
  }

  Protocol::Job *job = Factory::Protocol::Job::create();
  job->sendWhisp(to, msg);
  Network::Manager::Client::getInstance()->push(job);
}

void	GUIG::ChatBox::sendMsgGrp(const std::string &str) {
  std::string tmp = str.substr(2);

  size_t pos;
  size_t l = tmp.length();
  bool good = false;
  for (pos = 0 ; tmp.length() > pos ; ++pos) {
    if (tmp[pos] != ' ') {
      tmp = tmp.substr(pos);
      good = true;
      break ;
    }
  }
  if (!good) { return ; }

  Protocol::Job *job = Factory::Protocol::Job::create();
  job->sendMsgGroup(tmp);
  Network::Manager::Client::getInstance()->push(job);
}

void	GUIG::ChatBox::sendMsgGlob(const std::string& msg) {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->sendMsgGlob(msg);
  Network::Manager::Client::getInstance()->push(job);
}
