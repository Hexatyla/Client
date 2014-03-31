//
// Hexagon.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Feb 24 15:57:58 2014 geoffrey bauduin
// Last update Mon Feb 24 16:08:08 2014 geoffrey bauduin
//

#include	"Utils/Hexagon.hpp"

bool	Utils::inHexagon(double x_max, double y_max, double border,
			 bool rotate, double mouse_x, double mouse_y) {
  double a, b;
  double x1, y1, x2, y2;

  if (mouse_y > (y_max / 2))
    mouse_y = (y_max - 1) - mouse_y;
  if (mouse_x < (x_max / 2))
    mouse_x = ((x_max)/ 2) + (((x_max - 1)/ 2) - mouse_x);
  if (mouse_x >= (x_max - border) || mouse_y < border)
    return (false);
  mouse_y = -mouse_y;
  if (!rotate)
  {
    x1 = ((x_max - 1) / 2);
    y1 = -1 * (border);
    x2 = (y_max - border);
    y2 = -1 * ((x_max - (2 * border) + 2) / 4);
  }
  else
  {
    x1 = (y_max - border);
    y1 = -1 * ((x_max - 1) / 2);
    x2 = y_max - ((x_max - (2 * border) + 2) / 4);
    y2 = -1 * border;
  }
  a = (y1 - y2) / (x1 - x2);
  b = ((x1 * y2) - (x2 * y1)) / (x1 - x2);
  /*
  std::cout << "A(" << x1 << ";" << y1 << ")  B(" << x2 << ":" << y2 << ")" << std::endl;
  std::cout << "a = " << a << "; b = " << b << std::endl;
  std::cout << "y = ax + b = " << static_cast<int>(a * mouse_x + b) << " // my = " << mouse_y << " ; mx = " << mo    use_x<< std::endl;
  */
  if (static_cast<int>(a * mouse_x + b) < mouse_y)
  {
    return (false);
  }
  return (true);
}
