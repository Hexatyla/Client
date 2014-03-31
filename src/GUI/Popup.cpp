// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Popup.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Popup.hpp"

GUI::Popup::Popup(std::string const& name, unsigned int _depth) :
  AOverlaySceneManager("Popup", 10), run(false), PopupObject(name), depth(_depth), type(GUI::Popup::RESULT)
{
}

GUI::Popup::~Popup()
{
}

void  GUI::Popup::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  bg = this->addOverlayImage(winsize, Ogre::Vector2(460, 220), Ogre::Vector2(731, 350),
      "popup_imageBG_"+ PopupObject, "bg_blue_title.png", true);
  bg->changeZOrder(depth);
  popupInput = this->addInputText(winsize, Ogre::Vector2(377, 67), Ogre::Vector2(771, 410),
      "popup_input_" + PopupObject, "input_cadre.png", "", true);
  popupInput->changeZOrder(depth);
  BValidate = this->addButton(winsize, Ogre::Vector2(49, 56), Ogre::Vector2(903, 490),
      "popup_validate_" + PopupObject,  "form_validate.png");
  BValidate->changeZOrder(depth);
  BCancel = this->addButton(winsize, Ogre::Vector2(48, 56), Ogre::Vector2(973, 490),
      "popup_cancel_" + PopupObject,   "form_annul.png");
  BCancel->changeZOrder(depth);
  content = this->addInputText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(795, 370),
		     "popup_content_" + PopupObject, "empty.png", "Enter your data", true);
  content->changeZOrder(depth);
  content->setSizeFont(24);
  BAccept = this->addButton(winsize, Ogre::Vector2(48, 56), Ogre::Vector2(933, 490),
      "popup_accept_" + PopupObject,   "close_core.png");
  BAccept->changeZOrder(depth);
  // INIT scene
}

void  GUI::Popup::setAnswer(std::string const& key, std::string const& answer)
{
  answers[key] = answer;
}

std::string  GUI::Popup::getAnswer(std::string const& key)
{
  if (answers.find(key) != answers.end())
    return (answers[key]);
  return ("");
}

void  GUI::Popup::cleanAnswers()
{
  for (std::map<std::string, std::string>::iterator it = answers.begin();
        it != answers.end(); ++it)
    it->second = "";
}

void  GUI::Popup::accept()
{
}

void  GUI::Popup::cancel()
{
}

void  GUI::Popup::validate()
{
}

void  GUI::Popup::setType(GUI::Popup::TypeBox _type)
{
  type = _type;
  content->setVisible(false);
}

void  GUI::Popup::setType(GUI::Popup::TypeBox _type, std::string const& text)
{
  this->setVisible(true);
  this->cleanAnswers();
  type = _type;
  content->setText(text);
  if (type == GUI::Popup::INPUT)
  {
    popupInput->setVisible(true);
    popupInput->updatePosition(Ogre::Vector2(771, 410));
    content->setVisible(true);
    content->updatePosition(Ogre::Vector2(795, 370));

    BCancel->setVisible(true);
    BCancel->changeZOrder(depth);
    BCancel->updatePosition(Ogre::Vector2(973, 490));

    BValidate->setVisible(true);
    BValidate->changeZOrder(depth);
    BValidate->updatePosition(Ogre::Vector2(903, 490));

    BAccept->setVisible(false);
    BAccept->changeZOrder(0);
    BAccept->updatePosition(Ogre::Vector2(933, 490));
    bg->setSize(Ogre::Vector2(460, 220));
  }
  else if (type == GUI::Popup::RESULT)
  {
    popupInput->updatePosition(Ogre::Vector2(771, 410));
    popupInput->setVisible(false);
    content->setVisible(true);
    content->updatePosition(Ogre::Vector2(795, 360));

    BCancel->setVisible(false);
    BCancel->changeZOrder(0);
    BCancel->updatePosition(Ogre::Vector2(973, 490));

    BValidate->setVisible(false);
    BValidate->changeZOrder(0);
    BValidate->updatePosition(Ogre::Vector2(903, 490));

    BAccept->changeZOrder(depth);
    BAccept->setVisible(true);
    BAccept->updatePosition(Ogre::Vector2(933, 420));
    bg->setSize(Ogre::Vector2(460, 150));
  }
  else if (type == GUI::Popup::PROPOSITION)
  {
    popupInput->updatePosition(Ogre::Vector2(771, 410));
    popupInput->setVisible(false);
    content->setVisible(true);
    content->updatePosition(Ogre::Vector2(795, 360));

    BCancel->setVisible(true);
    BCancel->changeZOrder(depth);
    BCancel->updatePosition(Ogre::Vector2(973, 420));

    BValidate->setVisible(true);
    BValidate->changeZOrder(depth);
    BValidate->updatePosition(Ogre::Vector2(903, 420));

    BAccept->changeZOrder(0);
    BAccept->setVisible(false);
    BAccept->updatePosition(Ogre::Vector2(933, 490));
    bg->setSize(Ogre::Vector2(460, 220));
  }
}

void  GUI::Popup::setContent(const std::string& _name)
{
}

const std::string&  GUI::Popup::getInput()
{
  return (popupInput->getText());
}

void  GUI::Popup::exit()
{
}

void  GUI::Popup::draw()
{
  if (type == GUI::Popup::RESULT)
  {
  }
  else if (type == GUI::Popup::PROPOSITION)
  {
  }
}
