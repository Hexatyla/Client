// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   ___HPP__
# define  ___HPP__

#include  "utils/graphicException.hh"
#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/TextBox.hh"
#include  "Clock.hpp"

#include  "Protocol/Race.hpp"

#include  "GUIG/AGUIG.hpp"

namespace GUIG
{
  class Progress : public AGUIG, public AOverlaySceneManager
  {
    private:
      struct UserData
      {
        Race::Race    race;
        unsigned int  team;
        bool          endLoading;
      };
      std::map<std::string, UserData> users;
      OverlayImage    *bg;
      OverlayText     *pourcent;
      unsigned int myPourcent;
      unsigned int wx, wy;

    public:
      Progress();
      virtual ~Progress();

    public:
      virtual void init(unsigned int, unsigned int);
      virtual void draw();

    public:
      void  infoMember(const std::string&, Race::Race = Race::RANDOM, unsigned int = 0);
      void  infoMember(const std::string&, unsigned int, Race::Race = Race::RANDOM);
      bool  allIsReady();
      void  setRaceToMember(const std::string&, Race::Race);
      void  setTeamToMember(const std::string&, unsigned int);
      void  getReadyMember(const std::string&);
      void  setMyPourcent(unsigned int);
      unsigned int getMyPourcent();
  };
}

#endif  /* ___HPP__ */
