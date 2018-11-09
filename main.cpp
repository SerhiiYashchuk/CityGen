#include "GenericTypes.h"

int main()
{
  const CityGen::Vector2 v1 = { 10, 10 };
  const CityGen::Vector2 v2 = { 5, 5 };
  const CityGen::Vector2 sum = v1 + v2;
  const CityGen::Vector2 dif = v1 - v2;
  const CityGen::Vector2 mul = v2 * 2;
  const CityGen::Vector2 div = v1 / 2;
  const double length = v1.length();

  return 0;
}
