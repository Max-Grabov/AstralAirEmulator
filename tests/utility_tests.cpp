#include "binary_stream_util.hpp"
#include "gtest/gtest.h"
#include <vector>

TEST(UtilTest, TestGet)
{
  using namespace AstralAir::Utility;

  std::vector<std::byte> t{};
  t.emplace_back(std::byte(0));
  t.emplace_back(std::byte(1));
  t.emplace_back(std::byte(2));
  t.emplace_back(std::byte(3));

  uint32_t test_value{Get<uint32_t>(t, 0)};

  EXPECT_EQ(test_value, 0x03020100);
}
