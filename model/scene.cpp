#include "scene.hpp"

#include "entities/pointer_ent.hpp"
#include "geometry/primitives/point.hpp"
#include "geometry/primitives/segment.hpp"

Scene::Scene() = default;

const std::vector<PointEnt>& Scene::GetPoints() const
{
  return m_points;
}
const std::list<Segment>& Scene::GetSegments() const
{
  return m_segments;
}

void Scene::SetPoints(const std::vector<PointEnt>& points)
{
  m_points = points;
}

void Scene::AddPoint(const PointEnt& pt)
{
  m_points.push_back(pt);
}