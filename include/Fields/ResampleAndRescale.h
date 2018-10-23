#ifndef CITYGEN_RESAMPLE_AND_RESCALE_H
#define CITYGEN_RESAMPLE_AND_RESCALE_H

#include "Fields/IEigenField.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <type_traits>

namespace CityGen
{
template<class T>
class ResampleAndRescale : public IEigenField
{
private:
  using Vector2d = std::vector<std::vector<Vector2>>;

  // If an instance of this class outlives corresponding instance of ResampleAndRescale class,
  // then we'll be in trouble. Consider using a "life-guard".
  class EigenAccessor : public IVectorField
  {
  public:
    EigenAccessor(bool isMajor, const ResampleAndRescale<T> &field) : _isMajor(isMajor), _field(field) {}

    Vector sample(Vector pos) override
    {
      return _field.sample(_isMajor, pos);
    }

  private:
    const bool _isMajor = false;
    const ResampleAndRescale<T> &_field;
  };

  ResampleAndRescale(Vector2d majorVectors, Vector min, Vector max)
    : _majorEigenVectors(majorVectors), _min(min), _size(max - min),
      _isZeroSize(std::abs(_size.x) < std::numeric_limits<float>::epsilon() || std::abs(_size.y) < std::numeric_limits<float>::epsilon())
  {
    static_assert(std::is_base_of<IVectorField, T>(), "T should conform to IVectorField interface.");
    assert(!_isZeroSize);

    _major = EigenAccessor{ true, *this };
    _minor = EigenAccessor{ false, *this };
  }

  Vector sample(bool isMajor, Vector pos)
  {
    Vector res;

    if (!_isZeroSize)
    {
      const std::size_t size = _majorEigenVectors.size();
      const Vector p = { (pos - _min) / _size } * size;
      const std::size_t i = std::clamp(p.x, 0, size);
      const std::size_t j = std::clamp(p.y, 0, size);

      res = _majorEigenVectors[i][j];

      if (!isMajor)
      {
        res = { -res.y. res.x };
      }
    }

    return res;
  }

public:
  static ResampleAndRescale<T> create(const ITensorField &baseField, Vector min, Vector max, std::size_t res)
  {
    std::vector<std::vector<Vector>> majorVectors{ res + 1, std::vector<Vector>{ res + 1 } };

    for (std::size_t i = 0; i < majorVectors.size(); ++i)
    {
      auto &m = majorVectors[i];

      for (std::size_t j = 0; j < m.size(); ++j)
      {
        const Vector pos = { static_cast<float>(i) / res, static_cast<float>(j) / res } + min / Vector{ res, res };
        const Tensor t = baseField.sample(pos);

        std::tie(m[j], std::ignore) = t.eigenVectors();
      }
    }

    return ResampleAndRescale(majorVectors, min, max);
  }

  const IVectorField &majorEigenVectors() const override
  {
    return _major;
  }

  const IVectorField &minorEigenVectors() const override
  {
    return _minor;
  }

private:
  Vector2d _majorEigenVectors;

  T _major;
  T _minor;

  const Vector _size;
  const Vector _min;

  const bool _isZeroSize = false;
};
}

#endif
