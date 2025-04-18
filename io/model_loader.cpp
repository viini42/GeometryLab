#include "model_loader.hpp"

#include <fstream>

Ptr<Model> ModelLoader::Read(const std::filesystem::path& filepath)
{
  if (!std::filesystem::exists(filepath))
    return nullptr;

  std::ifstream file{ filepath };

  if (!file.is_open())
    return nullptr;

  std::list<Point> pts;

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    f64 x, y;
    if (iss >> x >> y)
    {
      pts.emplace_back(x, y); // Assuming Point has a constructor Point(float x, float y)
    }
    else
    {
      return nullptr;
    }
  }

  Ptr<Model> model = std::make_shared<Model>();
  model->SetPoints(pts);

  return model;
}