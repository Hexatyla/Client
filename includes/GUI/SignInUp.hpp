// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/SignInUp.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_SIGNINUP_HPP__
# define  __GUI_SIGNINUP_HPP__

#include  <string>
#include  <map>

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class SignInUp : public IGUI, public AOverlaySceneManager
  {
    public:
      enum typeObject
      {
        SIGNIN = 0,
        SIGNUP = 1
      };

    public:
      SignInUp();
      ~SignInUp();

    public:
      bool run;

    private:
      OverlayImage*   bg;
      OverlayImage*   black_bg;
      InputText *pseudo_i, *password_i, *mail_i;
      typeObject obj;

    public:
      virtual void init(unsigned int, unsigned int);
      void  validate(const std::string&, const std::string&, const std::string& mail = "");
      typeObject getType();
      void  signIn();
      void  signUp();
      void  exit();
      virtual void draw();
      std::string const&  getPseudo();
      std::string const&  getPassword();
      std::string const&  getMail();

    private:
      void  validateSignin(const std::string&, const std::string&);
      void  validateSignup(const std::string&, const std::string&, const std::string&);

  public:
    virtual InputText	*addInputText(Ogre::Vector2 const &, Ogre::Vector2 const &, Ogre::Vector2 const &, std::string const &, std::string const &, std::string const&, bool = false, bool = true);
  };
}

#endif /* !__GUI_SIGNINUP_HPP__ */
