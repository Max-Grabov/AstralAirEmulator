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

TEST(BinTest, TestDataReadHeader)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/voice.bin");
  View data_view("./AstralAirData/voice.bin");

  std::vector<AstralAirData> data{bin.OpenAndRead()};
  auto offset = data[0].GetOffset();
  auto size = data[0].GetData();
  auto result = data_view.Read(offset, size);
  EXPECT_EQ(static_cast<char>(result[0]), 'O');
  EXPECT_EQ(static_cast<char>(result[1]), 'g');
  EXPECT_EQ(static_cast<char>(result[2]), 'g');
  EXPECT_EQ(static_cast<char>(result[3]), 'S');
}
