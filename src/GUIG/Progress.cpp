// C/C++ File
// AUTHOR:    Kyndt
// MAIL:      clovis.kyndt@gmail.com
// FILE:      src/GUIG/AGUIG.cpp
// ROLE:      TODO (some explanation)
// CREATED:   2014-01-01 15:01:28
// MODIFIED:  2014-01-08 14:04:26

#include  "GUIG/Progress.hpp"

GUIG::Progress::Progress() : AOverlaySceneManager("GUIG_Progress", 20), bg(NULL), myPourcent(0), wx(0), wy(0)
{
}

GUIG::Progress::~Progress()
{
}

// virtual redefinie
void  GUIG::Progress::init(unsigned int x, unsigned int y)
{
  wx = x;
  wy = y;
  Ogre::Vector2 winsize(wx, wy);

  bg = this->addOverlayImage(winsize, Ogre::Vector2(1920, 1080), Ogre::Vector2(0, 0),
          "Progress_bg", "background.jpg", true);
  bg->changeZOrder(0);
  pourcent = this->addOverlayText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(900, 900),
        "Progress_pourcent", "empty.png", "0", true);
  pourcent->setVisible(false);
}

// virtual redefinie
void  GUIG::Progress::draw()
{
  std::map<unsigned int, std::vector<std::string>> rank;
  unsigned int n = 0;
  unsigned int u = 0;

  for (std::map<std::string, UserData>::iterator it = users.begin(); it != users.end(); ++it)
  {
    rank[(it->second).team];
    rank[(it->second).team].push_back(it->first);
  }

  for (std::map<unsigned int, std::vector<std::string>>::iterator it = rank.begin(); it != rank.end(); ++it)
  {
    u = 0;
    for (std::vector<std::string>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
    {
      OverlayText  *text  = dynamic_cast<OverlayText *>(getOverlay("Progress_pseudo_" + *it2));
      if (!text)
      {
        std::cout << "Unknow pseudo" << std::endl;
        return;
      }

      if (users[*it2].endLoading)
        text->setColor(Ogre::ColourValue(51.0 / 255.0, 255.0 / 255.0, 102.0 / 255.0));
      else
        text->setColor(Ogre::ColourValue(253.0 / 255.0, 253.0 / 255.0, 253.0 / 255.0));

      // Du coup pas plus de d'2 equipe !
      if (n == 0)
      {
        text->updatePosition(Ogre::Vector2(50, 20));
        text->setVisible(true);
        text->changeZOrder(10);
      }
      else if (n == 1)
      {
        text->updatePosition(Ogre::Vector2(1700, 20));
        text->setVisible(true);
        text->changeZOrder(10);
      }
      else
      {
        text->setVisible(false);
        text->changeZOrder(1);
      }
      u++;
    }
    n++;
  }
  std::ostringstream oss;
  oss << myPourcent;
  pourcent->setText(oss.str());
}

void  GUIG::Progress::infoMember(const std::string &pseudo, Race::Race r, unsigned int team)
{
  int previousSize = users.size();
  Ogre::Vector2 winsize(wx, wy);

  users[pseudo].race = r;
  users[pseudo].team = team;
  users[pseudo].endLoading = false;
  if (previousSize != users.size())
  {
     this->addOverlayText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(0, 0),
        "Progress_pseudo_" + pseudo, "empty.png", pseudo, true)->setVisible(false);
  }
  draw();
}

void  GUIG::Progress::infoMember(const std::string &pseudo, unsigned int team, Race::Race r)
{
  int previousSize = users.size();
  Ogre::Vector2 winsize(wx, wy);

  users[pseudo].race = r;
  users[pseudo].team = team;
  users[pseudo].endLoading = false;
  if (previousSize != users.size())
  {
     this->addOverlayText(winsize, Ogre::Vector2(400, 20), Ogre::Vector2(0, 0),
        "Progress_pseudo_" + pseudo, "empty.png", pseudo, true)->setVisible(false);
  }
  draw();
}

bool  GUIG::Progress::allIsReady()
{
  for (std::map<std::string, UserData>::iterator it = users.begin(); it != users.end(); ++it)
    if (!(it->second).endLoading)
      return (false);
  return (true);
}

void  GUIG::Progress::setRaceToMember(const std::string &pseudo, Race::Race r)
{
  if (users.find(pseudo) != users.end())
    users[pseudo].race = r;
  draw();
}

void  GUIG::Progress::setTeamToMember(const std::string &pseudo, unsigned int team)
{
  if (users.find(pseudo) != users.end())
    users[pseudo].team = team;
  draw();
}

void  GUIG::Progress::getReadyMember(const std::string &pseudo)
{
  if (users.find(pseudo) != users.end())
    users[pseudo].endLoading = true;
  draw();
}

void  GUIG::Progress::setMyPourcent(unsigned int v)
{
  myPourcent = v;
  draw();
}

unsigned int GUIG::Progress::getMyPourcent()
{
  return (myPourcent);
}
