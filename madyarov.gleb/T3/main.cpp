#include "Polygon.h"
using namespace madyarov;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  std::vector<Polygon> polygons = readPolygons(argv[1]);
  processCommands(polygons);
  return 0;
}
