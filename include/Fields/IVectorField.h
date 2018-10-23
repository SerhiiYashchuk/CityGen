#ifndef CITYGEN_I_VECTOR_FIELD_H
#define CITYGEN_I_VECTOR_FIELD_H

#include "GenericTypes.h"

namespace CityGen
{
class IVectorField
{
public:
  virtual ~IVectorField() = default;

  virtual Vector sample(Vector pos) const = 0;
};

namespace Utils
{
Vector correctVectorDirection(Vector v, Vector prev)
{
  return v == Vector{} || Utils::dotProduct(prev, v) ? v : Vector{ -v.x, -v.y };
}

Vector correctedSample(const IVectorField &field, Vector pos, Vector baseDirection)
{
  return correctVectorDirection(field.sample(pos), baseDirection);
}

Vector singleTraceVectorField(const IVectorField &field, Vector pos, Vector prev)
{
  const Vector k1 = correctedSample(field, pos, prev);
  const Vector k2 = correctedSample(field, pos + k1 / 2, prev);
  const Vector k3 = correctedSample(field, pos + k2 / 2, prev);
  const Vector k4 = correctedSample(field, pos + k3, prev);

  return correctVectorDirection(k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6, prev);
}

Vector traceVectorField(const IVectorField &field, Vector pos, Vector prev, float maxSegmentLength)
{
  Vector first = prev;
  Vector res;
  float lengthSum = 0;

  for (int i = 0; i < 10 && lengthSum < maxSegmentLength; ++i)
  {
    const Vector d = singleTraceVectorField(field, pos, prev);
    const float l = d.length();

    lengthSum += l;
    res += d;
    prev = d;

    if (Utils::dotProduct(first, d / l) < 0.9961)
      break;
  }

  return res;
}
}
}

#endif
