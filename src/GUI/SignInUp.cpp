
// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/SignInUp.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/SignInUp.hpp"

GUI::SignInUp::SignInUp() : AOverlaySceneManager("SignInUp", 10), run(false), obj(GUI::SignInUp::SIGNIN)
{
}

GUI::SignInUp::~SignInUp()
{
}

void  GUI::SignInUp::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  bg = this->addOverlayImage(winsize, Ogre::Vector2(461, 532), Ogre::Vector2(731, 150),
      "background_form", "popup_debug.png", true);
  bg->changeZOrder(20);
  pseudo_i = this->addInputText(winsize, Ogre::Vector2(377, 67), Ogre::Vector2(771, 310),
      "signinup_input_pseudo", "input_cadre.png", "pseudo");
  pseudo_i->setPaddingWidth(20);
  pseudo_i->setPaddingHeight(20);
  pseudo_i->changeZOrder(21);

  password_i = this->addInputText(winsize, Ogre::Vector2(377, 67), Ogre::Vector2(771, 410),
		     "signinup_input_password", "input_cadre.png", "password", true);
  password_i->changeZOrder(21);
  password_i->setPaddingWidth(20);
  password_i->setPaddingHeight(20);

  mail_i = this->addInputText(winsize, Ogre::Vector2(377, 67), Ogre::Vector2(771, 460),
		     "signinup_input_mail", "input_cadre.png", "mail", true);
  mail_i->addValidChar(".@_-");
  mail_i->setPaddingWidth(20);
  mail_i->setPaddingHeight(20);
  mail_i->changeZOrder(21);

  this->addButton(winsize, Ogre::Vector2(86, 19), Ogre::Vector2(840, 240),
      "signinup_signUp", "subscribe_text.png")->changeZOrder(21);
  this->addButton(winsize, Ogre::Vector2(72, 17), Ogre::Vector2(1000, 242),
      "signinup_signIn",   "connect_text.png")->changeZOrder(21);
  this->addButton(winsize, Ogre::Vector2(53, 60), Ogre::Vector2(903, 550),
      "signinup_validate",  "form_validate.png")->changeZOrder(21);
  this->addButton(winsize, Ogre::Vector2(48, 56), Ogre::Vector2(973, 550),
      "signinup_exit",   "form_annul.png")->changeZOrder(21);
  mail_i->setVisible(false);
  black_bg = this->addOverlayImage(winsize, Ogre::Vector2(winX, winY), Ogre::Vector2(0, 0),
      "signinup_blackBg", "black.png");
  black_bg->setOpacity(0.6);
  black_bg->changeZOrder(18);
}

void  GUI::SignInUp::validateSignin(const std::string& user, const std::string& password)
{
}

void  GUI::SignInUp::validateSignup(const std::string& user, const std::string& password, const std::string& mail)
{
}

void  GUI::SignInUp::validate(const std::string& user, const std::string& password, const std::string& mail)
{
  if (obj == GUI::SignInUp::SIGNIN)
  {
    validateSignin(user, password);
  }
  else if (obj == GUI::SignInUp::SIGNUP)
  {
    validateSignup(user, password, mail);
  }
}

void  GUI::SignInUp::signUp()
{
  obj = GUI::SignInUp::SIGNUP;
  mail_i->setVisible(true);
  pseudo_i->updatePosition(Ogre::Vector2(771, 280));
  password_i->updatePosition(Ogre::Vector2(771, 370));
  black_bg->setVisible(true);
}

void  GUI::SignInUp::signIn()
{
  obj = GUI::SignInUp::SIGNIN;
  mail_i->setVisible(false);
  pseudo_i->updatePosition(Ogre::Vector2(771, 310));
  password_i->updatePosition(Ogre::Vector2(771, 410));
  black_bg->setVisible(true);
}

void  GUI::SignInUp::exit()
{
  this->setVisible(false);
}

void  GUI::SignInUp::draw()
{
  if (obj == GUI::SignInUp::SIGNIN)
  {
  }
  else if (obj == GUI::SignInUp::SIGNUP)
  {
  }
}

std::string const& GUI::SignInUp::getPseudo()
{
  return (pseudo_i->getText());
}

std::string const& GUI::SignInUp::getPassword()
{
  return (password_i->getRealText());
}

std::string const& GUI::SignInUp::getMail()
{

  return (mail_i->getText());
}

GUI::SignInUp::typeObject GUI::SignInUp::getType()
{
  return (obj);
}

InputText	*GUI::SignInUp::addInputText(Ogre::Vector2 const &winSize, Ogre::Vector2 const &size, Ogre::Vector2 const &pos, std::string const &name, std::string const &pathname, std::string const &text, bool locked, bool visible)
{
  InputText *tmp = AOverlaySceneManager::addInputText(winSize, size, pos, name, pathname, text, locked, visible);

  tmp->setTextPos(Ogre::Vector2(1000, 1000));
  tmp->setSizeMax(15);
  return tmp;
}
