#ifndef SCENE_HPP
#define SCENE_HPP

#include "entities/pointer_ent.hpp"
#include "geometry/primitives/point.hpp"
#include "geometry/primitives/segment.hpp"

#include <list>
#include <vector>

struct Segment;
class Scene
{
public:
  Scene();

  [[nodiscard]] const std::vector<PointEnt>& GetPoints() const;
  [[nodiscard]] const std::list<Segment>& GetSegments() const;

  void SetPoints(const std::vector<PointEnt>& points);
  void AddPoint(const PointEnt& pt);

private:
  std::vector<PointEnt> m_points;
  std::list<Segment> m_segments;
};

#endif // MODEL_HPP
