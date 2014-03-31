// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Core.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include  "GUI/Core.hpp"

GUI::Core::Core() : AOverlaySceneManager("Core", 10), run(true), type(GUI::Core::HOME), time(), gameStart(false)
{
}

GUI::Core::~Core()
{
}

void  GUI::Core::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  Bsetting = this->addButton(winsize, Ogre::Vector2(45, 52), Ogre::Vector2(670, 620),
      "core_setting", "setting.png");
  bg = this->addOverlayImage(winsize, Ogre::Vector2(234, 270), Ogre::Vector2(703, 415),
      "choice_game_type_background", "choice_game_type_background.png", true);
  Bspeed1 = this->addButton(winsize, Ogre::Vector2(88, 101), Ogre::Vector2(846, 460),
      "core_launchSpeed1", "choice_game_type_1v1.png");
  Bspeed1->changeZOrder(1);
  Bspeed3 = this->addButton(winsize, Ogre::Vector2(88, 101), Ogre::Vector2(754, 460),
      "core_launchSpeed3", "choice_game_type_3v3.png");
  Bspeed2 = this->addButton(winsize, Ogre::Vector2(88, 101), Ogre::Vector2(800, 538),
      "core_launchSpeed2", "choice_game_type_2v2.png");
  Bteam = this->addButton(winsize, Ogre::Vector2(88, 101), Ogre::Vector2(708, 538),
      "core_createGroup", "choice_game_type_team.png");
  Bspeed3->changeZOrder(1);
  Bspeed2->changeZOrder(1);
  Bteam->changeZOrder(1);
  /* PROFIL */
  Bprofile = this->addButton(winsize, Ogre::Vector2(87, 101), Ogre::Vector2(820, 338),
      "profil_*", "profil_principal.png");
  Bprofile_min = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(805, 336),
      "friends_addFriend", "profil_add.png");
  Bprofile_add = this->addButton(winsize, Ogre::Vector2(28, 24), Ogre::Vector2(789, 358),
      "friends_rmFriend", "profil_min.png");
  /* CLOSE_CORE */
  Bclose = this->addButton(winsize, Ogre::Vector2(48, 56), Ogre::Vector2(10, 10),
      "core_back",   "close_core.png");
  /* LAUNCH */
  Blaunch = this->addButton(winsize, Ogre::Vector2(95, 110), Ogre::Vector2(910, 10),
      "core_launch",   "launcher.png");
  /* image CORE : ACTIF */
  w1 = this->addOverlayImage(winsize, Ogre::Vector2(316, 365), Ogre::Vector2(294, 159),
      "wallpaper1", "wallpaper_1.png", true);
  w2 = this->addOverlayImage(winsize, Ogre::Vector2(221, 255), Ogre::Vector2(640, 650),
      "wallpaper2", "wallpaper_2.png", true);
  w3 = this->addOverlayImage(winsize, Ogre::Vector2(175, 200), Ogre::Vector2(613, 281),
      "wallpaper3", "wallpaper_3.png", true);
  w4 = this->addOverlayImage(winsize, Ogre::Vector2(174, 194), Ogre::Vector2(523, 433),
      "wallpaper4", "wallpaper_4.png", true);
  w5 = this->addOverlayImage(winsize, Ogre::Vector2(84, 97), Ogre::Vector2(895, 620),
      "wallpaper5", "wallpaper_5.png", true);
  w6 = this->addOverlayImage(winsize, Ogre::Vector2(65, 75), Ogre::Vector2(772, 266),
      "wallpaper6", "wallpaper_6.png", true);
  /*
  this->addButton(winsize, Ogre::Vector2(492, 578), Ogre::Vector2(0, 0),
      "test", "test.png");
      */
  Bplay = this->addButton(winsize, Ogre::Vector2(234, 270), Ogre::Vector2(703, 415),
      "core_play", "ButtonPlay.png");
  Bplay->changeZOrder(1);
  w6->updatePosition(Ogre::Vector2(719, 652));
  w6->changeZOrder(0);
  w5->updatePosition(Ogre::Vector2(935, 446));
  w5->changeZOrder(0);
  w4->updatePosition(Ogre::Vector2(523, 433));
  w4->changeZOrder(0);
  w3->updatePosition(Ogre::Vector2(613, 281));
  w3->changeZOrder(0);
  w2->updatePosition(Ogre::Vector2(780, 650));
  w2->changeZOrder(0);
  w1->updatePosition(Ogre::Vector2(1035, 272));
  w1->changeZOrder(0);
  Bonline = this->addButton(winsize, Ogre::Vector2(118, 136), Ogre::Vector2(879, 344),
      "core_connectOnline", "ButtonOnline.png");
  Bcampagne = this->addButton(winsize, Ogre::Vector2(116, 135), Ogre::Vector2(940, 550),
      "core_campagne", "ButtonCampagne.png");
//  this->addOverlayImage(winsize, Ogre::Vector2(80, 80), Ogre::Vector2(975, 450),
//      "imageMenu2", "imageMenu2.png", true);
//  this->addOverlayImage(winsize, Ogre::Vector2(300, 300), Ogre::Vector2(780, 650),
//      "imageMenu3", "imageMenu3.png", true);
//  this->addOverlayImage(winsize, Ogre::Vector2(110, 110), Ogre::Vector2(645, 660),
//      "imageMenu4", "imageMenu4.png", true);
//  this->addOverlayImage(winsize, Ogre::Vector2(220, 220), Ogre::Vector2(430, 425),
//      "imageMenu5", "imageMenu5.png", true);
//  this->addOverlayImage(winsize, Ogre::Vector2(260, 260), Ogre::Vector2(525, 210),
//      "imageMenu6", "imageMenu6.png", true);
//  this->addOverlayImage(winsize, Ogre::Vector2(90, 90), Ogre::Vector2(790, 300),
//      "imageMenu7", "imageMenu7.png", true);
  black = this->addOverlayImage(winsize, Ogre::Vector2(winX, winY), Ogre::Vector2(0, 0),
      "black", "black.png");

  pseudo_core = this->addOverlayText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(70, 30),
      "core_pseudo", "empty.png", "", true);
  pseudo_core->setSizeFont(16);
  time_text   = this->addOverlayText(winsize, Ogre::Vector2(100, 20), Ogre::Vector2(932, 57),
      "timeElapsed", "empty.png", "--:--", true);
  time_text->changeZOrder(2);
  time_text->setColor(Ogre::ColourValue(0.0f, 0.8f, 1.0f));
  time_bg     = this->addOverlayImage(winsize, Ogre::Vector2(95, 110), Ogre::Vector2(910, 10),
                  "coe_launcherBlank", "launcher_blank.png", true);
  time_bg->changeZOrder(1);
  black->setOpacity(0.3);
  black->changeZOrder(1);
}

void  GUI::Core::setType(GUI::Core::Type _type)
{
  type = _type;
  draw();
}

void  GUI::Core::startGame()
{
  gameStart = true;
  time.init();
  draw();
}

void  GUI::Core::stopGame()
{
  gameStart = false;
}

bool  GUI::Core::gameIsStarting()
{
  return (gameStart);
}

GUI::Core::Type GUI::Core::getType()
{
  return (type);
}

void  GUI::Core::moveBlackScreen(unsigned int z)
{
  black->changeZOrder(z);
}

void  GUI::Core::cancelGame()
{
}

void  GUI::Core::createGroup()
{
}

void  GUI::Core::connectOnline()
{
}

void  GUI::Core::play()
{
}

void  GUI::Core::launch()
{
}

void  GUI::Core::launchSpeed3()
{
}

void  GUI::Core::launchSpeed2()
{
}

void  GUI::Core::launchSpeed1()
{
}

void  GUI::Core::setting()
{
}

void  GUI::Core::setUser(std::string const &_user)
{
  user = _user;
}

const std::string &GUI::Core::getUser()
{
  return (user);
}

void  GUI::Core::back()
{
  type = GUI::Core::HOME;
}

void  GUI::Core::draw()
{
  if (type == GUI::Core::HOME)
  {
    w6->updatePosition(Ogre::Vector2(719, 652));
    w5->updatePosition(Ogre::Vector2(941, 457));
    w4->updatePosition(Ogre::Vector2(523, 433));
    w3->updatePosition(Ogre::Vector2(613, 281));
    w2->updatePosition(Ogre::Vector2(799, 637));
    w1->updatePosition(Ogre::Vector2(1030, 290));
    Bplay->setVisible(true);
    Bplay->changeZOrder(1);
    Bcampagne->setVisible(true);
    Bonline->setVisible(true);
    bg->changeZOrder(0);
    bg->setVisible(false);
    Blaunch->setVisible(false);
    Bclose->setVisible(false);
    Bprofile_add->setVisible(false);
    Bprofile_min->setVisible(false);
    Bprofile->setVisible(false);
    Bteam->setVisible(false);
    Bspeed2->setVisible(false);
    Bspeed3->setVisible(false);
    Bspeed1->setVisible(false);
    pseudo_core->setVisible(false);
    time_text->setVisible(false);
    time_bg->setVisible(false);
  }
  else
  {
    w6->updatePosition(Ogre::Vector2(772, 266));
    w5->updatePosition(Ogre::Vector2(895, 620));
    w4->updatePosition(Ogre::Vector2(523, 433));
    w3->updatePosition(Ogre::Vector2(613, 281));
    w2->updatePosition(Ogre::Vector2(640, 650));
    w1->updatePosition(Ogre::Vector2(294, 159));
    if (gameStart)
    {
      time_bg->setVisible(true);
      time_text->setVisible(true);
      time_text->setText(time.getTimeToString(1));
      Blaunch->setVisible(false);
    }
    else
    {
      Blaunch->setVisible(true);
      time_text->setVisible(false);
    time_bg->setVisible(false);
    }
    Bplay->setVisible(false);
    Bplay->changeZOrder(0);
    Bcampagne->setVisible(false);
    Bonline->setVisible(false);
    bg->changeZOrder(0);
    bg->setVisible(true);
    Bclose->setVisible(true);
    Bprofile_add->setVisible(true);
    Bprofile_min->setVisible(true);
    Bprofile->setVisible(true);
    Bteam->setVisible(true);
    Bspeed2->setVisible(true);
    Bspeed3->setVisible(true);
    Bspeed1->setVisible(true);
    pseudo_core->setText(user);
    pseudo_core->setVisible(true);
  }
}
