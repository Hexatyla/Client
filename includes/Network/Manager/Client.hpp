//
// Client.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 16:36:27 2014 gautier lefebvre
// Last update Sat Mar 15 14:54:51 2014 gautier lefebvre
//

#ifndef		__NETWORK_MANAGER_CLIENT_HPP__
#define		__NETWORK_MANAGER_CLIENT_HPP__

#include	<sys/time.h>
#include	<vector>

#include	"Network/Socket.hpp"
#include	"Protocol/Job.hpp"
#include	"SList.hpp"
#include	"Threading/Mutex.hpp"
#include	"Singleton.hpp"

namespace	Network {
  namespace	Manager {
    class	Client :public Singleton<Network::Manager::Client> {
      friend class Singleton<Network::Manager::Client>;

    private:
      Mutex		*_mutex;
      std::string	_host;
      int		_port;
      Network::SSocket	_socket;
      struct timeval	_clock;
      SList<Protocol::Job*>	_jobs;

      void	reinitClock();
      void	disconnect();
      void	connect();

    public:
      Client();
      ~Client();

      void	init(const std::string &, int);
      void	run();

      void	push(Protocol::Job *);
      Protocol::Job *getJob();
      size_t	getNbJob();

      void	reconnect();
    };
  }
}

void*		start_network_manager(void*);

#endif
