#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <vector>

#include "poly.h"

namespace command
{
  int isInputNumber( const std::string &str );
  void area( const std::vector<usikov::Polygon> &data );
  void min( const std::vector<usikov::Polygon> &data );
  void max( const std::vector<usikov::Polygon> &data );
  void count( const std::vector<usikov::Polygon> &data );
  void rmecho( std::vector<usikov::Polygon> &data );
  void intersections( const std::vector<usikov::Polygon> &data );
}

#endif // __COMMAND_H_
