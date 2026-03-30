#ifndef DRAWER_MODELLOADER_HPP
#define DRAWER_MODELLOADER_HPP

#include "../model/scene.hpp"
#include "utils/aliases.hpp"

#include <filesystem>

class ModelLoader
{
public:
  static Ptr<Model> Read(const std::filesystem::path& filepath);
};

#endif // DRAWER_MODELLOADER_HPP
