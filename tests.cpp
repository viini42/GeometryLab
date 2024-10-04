#include "world_converter.hpp"

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(WorldConverter, Constructor)
{
  const World world{ 640, 480 };
  const auto& [start, end, top, bot] = world.GetLimits();
  ASSERT_EQ(start, 0);
  ASSERT_EQ(bot, 0);
  ASSERT_EQ(end, 1);
  ASSERT_EQ(top, 0.75);
}

TEST(WorldConverter, ConvertToWorld)
{
  const World world{ 800, 600 };
  {
    constexpr i32 screen_x = 328;
    constexpr i32 screen_y = 306;
    const auto world_coords = world.ConvertToWorld(screen_x, screen_y);
    ASSERT_DOUBLE_EQ(world_coords.x, 0.41);
    ASSERT_DOUBLE_EQ(world_coords.y, 0.3675);
  }
  {
    constexpr i32 screen_x = 240;
    constexpr i32 screen_y = 210;
    const auto world_coords = world.ConvertToWorld(screen_x, screen_y);
    ASSERT_DOUBLE_EQ(world_coords.x, 0.30);
    ASSERT_DOUBLE_EQ(world_coords.y, 0.4875);
  }
}

TEST(WorldConverter, ConvertToScreen)
{
  const World world{ 800, 600 };
  {
    constexpr f64 world_x = 0.41;
    constexpr f64 world_y = 0.3675;
    const auto screen_coords = world.ConvertToScreen(world_x, world_y);
    ASSERT_EQ(screen_coords.x, 328);
    ASSERT_EQ(screen_coords.y, 306);
  }

  {
    constexpr f64 world_x = 0.30;
    constexpr f64 world_y = 0.4875;
    const auto screen_coords = world.ConvertToScreen(world_x, world_y);
    ASSERT_EQ(screen_coords.x, 240);
    ASSERT_EQ(screen_coords.y, 210);
  }
}

TEST(WorldConverter, MoveLeft)
{
  World world{ 800, 600 };
  world.MoveHorizontally(0.5);
  {
    constexpr f64 world_x = 0.91;
    constexpr f64 world_y = 0.3675;
    const auto screen_coords = world.ConvertToScreen(world_x, world_y);
    ASSERT_EQ(screen_coords.x, 328);
    ASSERT_EQ(screen_coords.y, 306);
  }
  {
    constexpr i32 screen_x = 328;
    constexpr i32 screen_y = 306;
    const auto world_coords = world.ConvertToWorld(screen_x, screen_y);
    ASSERT_DOUBLE_EQ(world_coords.x, 0.91);
    ASSERT_DOUBLE_EQ(world_coords.y, 0.3675);
  }
}
