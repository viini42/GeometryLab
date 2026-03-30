#ifndef GEOMETRYLAB_WORLD_LIMITS_HPP
#define GEOMETRYLAB_WORLD_LIMITS_HPP

#include "common/number_aliases.hpp"

struct WorldLimits
{
  f64 start;
  f64 end;
  f64 top;
  f64 bot;

  void Increase(f64 percentFactor);

  void Decrease(f64 percentFactor);
};

#endif // GEOMETRYLAB_WORLD_LIMITS_HPP
