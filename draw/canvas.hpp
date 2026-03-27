#ifndef DRAWER_CANVAS_HPP
#define DRAWER_CANVAS_HPP

#include "domain/model.hpp"
#include "utils/aliases.hpp"

class Canvas
{
public:
  Canvas(u64 width, u64 height);

private:
  u64 m_width;
  u64 m_height;
  Opt<Model> m_current_model;
};

#endif // DRAWER_CANVAS_HPP
