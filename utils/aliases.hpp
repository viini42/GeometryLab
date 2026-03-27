#ifndef DRAWER_ALIASES_HPP
#define DRAWER_ALIASES_HPP

#include <memory>
#include <optional>

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using Opt = std::optional<T>;

#endif // DRAWER_ALIASES_HPP
