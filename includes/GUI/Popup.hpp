// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     map/GUI/Popup.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_POPUP_HPP__
# define  __GUI_POPUP_HPP__

#include  <string>

#include  "overlays/TextBox.hh"
#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class Popup : public IGUI, public AOverlaySceneManager
  {
    public:
      enum TypeBox
      {
        RESULT = 0,
        PROPOSITION,
        INPUT,
      };

    public:
      Popup(std::string const&, unsigned int);
      ~Popup();

    public:
      bool run;

    private:
      std::string PopupObject;
      OverlayText   *content;
      OverlayImage  *bg;
      Button        *BValidate, *BAccept, *BCancel;
      InputText     *popupInput;
      unsigned int depth;
      std::map<std::string, std::string> answers;
      TypeBox type;

    public:
      virtual void  init(unsigned int, unsigned int);
      void  setAnswer(const std::string&, const std::string&);
      const std::string& getInput();
      std::string getAnswer(const std::string &key);
      void  cleanAnswers();
      void  exit();
      void  accept();
      void  cancel();
      void  validate();
      void  setType(GUI::Popup::TypeBox);
      void  setType(GUI::Popup::TypeBox, std::string const&);
      void  setContent(const std::string& _name);
      virtual void draw();
  };
}

#endif /* !__GUI_POPUP_HPP___ */
