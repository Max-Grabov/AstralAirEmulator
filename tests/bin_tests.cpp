#include "bin.hpp"
#include "data.hpp"

#include "gtest/gtest.h"

#include <array>

TEST(BinTest, TestVoiceOpen)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;

  BinFormat bin("./AstralAirData/voice.bin");

  std::vector<AstralAirData> data{bin.OpenAndRead()};
  std::array<char, 9> comparison = {'0', '0', '0', '0', '0', '0', '0', '1', '0'};

  EXPECT_EQ(33048, data.size());

  for(size_t it{0}; it < 9; ++it)
  {
    EXPECT_EQ(static_cast<char>(data[0].GetName()[it]), comparison[it]);
  }
}
