//
// Client.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Thu Mar  6 13:25:27 2014 geoffrey bauduin
// Last update Thu Mar  6 13:37:51 2014 geoffrey bauduin
//

#ifndef FACTORY_CLIENT_HPP_
# define FACTORY_CLIENT_HPP_

#include	"3DElements/Element3DContainer.hh"

namespace	Factory {

  namespace	Client {

    void	init(void);
    void	end(void);

    class	Element3D {

    public:
      static ::Element3DContainer	*create(Ogre::SceneManager *, const std::string &, const std::string &,
						OverlayImage *, const std::string &);
      static void	remove(::Element3DContainer *);

    };

  };

}

#endif
