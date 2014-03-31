#include	"Ogre.h"
#include	"applications/Application.hh"
#include	<cstdlib>

int	main(int ac, char **av)
{
  std::string host;
  int	port;

  if (ac == 3) {
    host = av[1];
    port = atoi(av[2]);
  }
  else {
    host = "localhost";
    port = 4242;
  }
  try {
    Application::getInstance()->exec(host, port);
  }
  catch (std::exception& e) {
    std::cerr  << "An exception has occurred: " << e.what() << std::endl;
    exit (0);
  }
  return 0;
}
