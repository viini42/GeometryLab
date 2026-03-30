#include "world_limits.hpp"

void WorldLimits::Increase(f64 percentFactor)
{
  auto value_hor = (end - start) * percentFactor;
  start -= value_hor / 2.0;
  end += value_hor / 2.0;
  auto value_ver = (top - bot) * percentFactor;
  bot -= value_ver / 2.0;
  top += value_ver / 2.0;
}
void WorldLimits::Decrease(f64 percentFactor)
{
  auto value_hor = (end - start) * percentFactor;
  start += value_hor / 2.0;
  end -= value_hor / 2.0;
  auto value_ver = (top - bot) * percentFactor;
  bot += value_ver / 2.0;
  top -= value_ver / 2.0;
}
