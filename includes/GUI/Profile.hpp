// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/Profil.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_PROFILE_HPP__
# define  __GUI_PROFILE_HPP__

#include  <string>

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class Profile : public IGUI, public AOverlaySceneManager
  {
    struct DataUser
    {
      std::string name;
      std::string mail;
      unsigned int VR1;
      unsigned int VR2;
      unsigned int VR3;
    };

    public:
      Profile();
      ~Profile();

    public:
      bool run;
      bool my;

    private:
      GUI::Profile::DataUser myData;
      GUI::Profile::DataUser userdata;

    public:
      virtual void init(unsigned int, unsigned int);
      void  exit();
      void updateMyUserData(const std::string& user, const std::string& mail = "",
                             unsigned int r1 = 0, unsigned int r2 = 0, unsigned int r3 = 0);
      void updateUserData(const std::string& user, const std::string& mail = "",
                            unsigned int r1 = 0, unsigned int r2 = 0, unsigned int r3 = 0);
      virtual void draw();
  };
}

#endif /* !__GUI_PROFILE_HPP__ */
