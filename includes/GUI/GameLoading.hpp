// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUI/GameLoading.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUI_GAMELOADING_HPP__
# define  __GUI_GAMELOADING_HPP__

#include  <string>
#include  <map>

#include  "overlays/AOverlaySceneManager.hh"
#include  "GUI/IGUI.hpp"

namespace GUI
{
  class GameLoading : public IGUI, public AOverlaySceneManager
  {
    public:
      GameLoading(const std::string&);
      ~GameLoading();

    private:
      std::string   me;
      std::map<std::string, unsigned int> playerToEquip;
      std::map<std::string, bool> playerToActif;
      unsigned int  actElement;
      unsigned int  pourcent;
      unsigned int  maxElement;

    public:
      virtual void init(unsigned int, unsigned int);
      bool  infoPlayer(const std::string&, bool actif, unsigned int  equip);
      bool  infoPlayer(const std::string&, bool actif);
      void  map(void); // a definir
      void  setMaxElement(unsigned int _max);
      unsigned int  calc(unsigned int _actElement);
      virtual void draw();
  };
}

#endif  /* !__GUI_GAMELOADING_HPP__ */
