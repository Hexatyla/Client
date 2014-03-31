//
// Client.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Tue Jan 21 14:02:59 2014 gautier lefebvre
// Last update Sat Mar 15 14:54:38 2014 gautier lefebvre
//

#include	<iostream>
#include	<unistd.h>

#include	"Factory/Protocol.hpp"
#include	"Network/Manager/Client.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Network/Exception.hpp"
#include	"Logger.hpp"
#include	"Converter.hpp"

#define		LOCK_NETWORK	ScopeLock scopelocknetwork(this->_mutex)
#define		LOG(x, y)	Logger::getInstance()->log((x),(y))

Network::Manager::Client::Client():
  _mutex(new Mutex()),
  _socket(),
  _clock(),
  _jobs()
{}

Network::Manager::Client::~Client() {}

void		Network::Manager::Client::disconnect() {
  this->_socket.destroy();
  for (auto job : this->_jobs) {
    Factory::Protocol::Job::remove(job);
  }
  this->_jobs.clear();
}

void		Network::Manager::Client::connect() {
  LOG("Creating socket", Logger::INFORMATION);
  this->_socket.create();
  LOG(std::string("Connecting to ") + this->_host + ":" + Converter::StringOf<int>(this->_port), Logger::INFORMATION);
  this->_socket.connect(this->_host, this->_port);
}

void		Network::Manager::Client::reconnect() {
  LOCK_NETWORK;
  this->disconnect();
  this->connect();
}

void		Network::Manager::Client::init(const std::string &host, int port) {
  LOG("Initializing Network", Logger::INFORMATION);
  this->_host = host;
  this->_port = port;
  this->connect();
  LOG("Network initialized", Logger::INFORMATION);
}

void		Network::Manager::Client::reinitClock() {
  this->_clock.tv_sec = 0;
  this->_clock.tv_usec = 40000;
}

void		Network::Manager::Client::run() {
  try {
    fd_set	rset, wset;

    while (true) {
      FD_ZERO(&rset);
      FD_ZERO(&wset);
      FD_SET(this->_socket.getFD(), &rset);
      if (this->_socket.hasSomethingToSend()) {
	FD_SET(this->_socket.getFD(), &wset);
      }
      this->reinitClock();
      select(this->_socket.getFD() + 1, &rset, &wset, NULL, &(this->_clock));
      if (FD_ISSET(this->_socket.getFD(), &wset)) {
	this->_socket.send();
      }
      if (FD_ISSET(this->_socket.getFD(), &rset)) {
	this->_socket.recv();
      }

      while (this->_socket.hasNewJob()) {
	Protocol::Job *job = this->_socket.getNextJob();
	if (job) {
	  ScopeLock s(&(this->_jobs));
	  this->_jobs.push_back(job);
	}
      }
    }
  }

  catch (Network::Exception *e) {
    std::cout << e->what() << std::endl;
    delete (e);
    Protocol::Job *job = Factory::Protocol::Job::create();
    job->exit();
    {
      ScopeLock(&(this->_jobs));
      this->_jobs.push_back(job);
    }
    while (1) { usleep(50000); }
  }
}

Protocol::Job *Network::Manager::Client::getJob() {
  LOCK_NETWORK;
  ScopeLock s(&this->_jobs);
  if (this->_jobs.empty()) {
    return (NULL);
  }
  Protocol::Job *job = this->_jobs.front();
  this->_jobs.pop_front();
  return (job);
}

size_t		Network::Manager::Client::getNbJob() {
  LOCK_NETWORK;
  ScopeLock s(&this->_jobs);
  if (this->_jobs.empty()) {
    return (0);
  }
  return (this->_jobs.size());
}

void		Network::Manager::Client::push(Protocol::Job *job) {
  LOCK_NETWORK;
  if (job) {
    this->_socket.push(job);
  }
}

void		*start_network_manager(void *ptr) {
  Network::Manager::Client *nm = reinterpret_cast<Network::Manager::Client*>(ptr);
  nm->run();
  return (nm);
}
