#include <iostream>
#include "program.h"

int main(int /*argc*/, char const * /*argv[]*/)
{
  CityGen::Program program({ 1366, 768 }, "SFML Graph Implementation");
  program.run();

  return 0;
}
