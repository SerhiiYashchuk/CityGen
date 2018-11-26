#ifndef CITYGEN_I_EIGEN_FIELD_H
#define CITYGEN_I_EIGEN_FIELD_H

#include "Fields/IVectorField.h"

namespace CityGen
{
class IEigenField
{
public:
  virtual ~IEigenField() = default;

  virtual const IVectorField &majorEigenVectors() const = 0;
  virtual const IVectorField &minorEigenVectors() const = 0;
};
}

#endif
