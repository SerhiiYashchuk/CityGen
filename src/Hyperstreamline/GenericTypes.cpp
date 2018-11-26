#include "GenericTypes.h"

namespace CityGen
{
namespace Utils
{
float dotProduct(Vector v1, Vector v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
}
}