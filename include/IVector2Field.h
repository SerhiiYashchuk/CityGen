#ifndef CITYGEN_I_VECTOR2_FIELD_H
#define CITYGEN_I_VECTOR2_FIELD_H

#include "GenericTypes.h"

namespace CityGen
{
class IVector2Field
{
public:
  virtual ~IVector2Field() = default;

  virtual Vector2 sample(Vector2 pos) = 0;
};

namespace Utils
{
Vector2 correctVectorDirection(Vector2 v, Vector2 prev)
{
  return v == Vector2{} || Utils::dotProduct(prev, v) ? v : -v;
}

Vector2 correctedSample(const IVector2Field &field, Vector2 pos, Vector2 baseDirection)
{
  return correctVectorDirection(field.sample(pos), baseDirection);
}

Vector2 singleTraceVectorField(const IVector2Field &field, Vector2 pos, Vector2 prev)
{
  const Vector2 k1 = correctedSample(pos, prev);
  const Vector2 k2 = correctedSample(pos + k1 / 2, prev);
  const Vector2 k3 = correctedSample(pos + k2 / 2, prev);
  const Vector2 k4 = correctedSample(pos + k3, prev);

  return correctVectorDirection(k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6, prev);
}

Vector2 traceVectorField(const IVector2Field &field, Vector2 pos, Vector2 prev, float maxSegmentLength)
{
  Vector2 first = prev;
  Vector2 res;
  float lengthSum = 0;

  for (int i = 0; i < 10 && lengthSum < maxSegmentLength; ++i)
  {
    const Vector2 d = singleTraceVectorField(field, pos, prev);
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
