// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     src/GUI/Profile.cpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#include "GUI/Profile.hpp"

GUI::Profile::Profile() :  AOverlaySceneManager("Profile", 10), run(false), my(true)
{
}

GUI::Profile::~Profile()
{
}

void  GUI::Profile::init(unsigned int winX, unsigned int winY)
{
  Ogre::Vector2 winsize(winX, winY);

  // INIT scene
}

void  GUI::Profile::updateMyUserData(const std::string& user, const std::string& mail,
                                      unsigned int r1, unsigned int r2, unsigned int r3)
{
  myData.name = user;
  myData.mail = mail;
  myData.VR1 = r1;
  myData.VR2 = r2;
  myData.VR3 = r3;
}

void  GUI::Profile::updateUserData(const std::string& user, const std::string& mail,
                                      unsigned int r1, unsigned int r2, unsigned int r3)
{
  userdata.name = user;
  userdata.mail = mail;
  userdata.VR1 = r1;
  userdata.VR2 = r2;
  userdata.VR3 = r3;
}

void  GUI::Profile::exit()
{
}

void  GUI::Profile::draw()
{
  /* draw my user player information's */
  if (my == true)
  {
  }
  /* draw an other player information's */
  else
  {
  }
}
