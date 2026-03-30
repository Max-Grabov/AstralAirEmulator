#include "../../src/data/data.hpp"
#include "../../src/formats/bin.hpp"

#include "gtest/gtest.h"

#include <string>
#include <array>

TEST(BinTest, TestOpen)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;

  BinFormat bin("./AstralAirData/voice.bin");

  std::vector<AstralAirData> data{bin.OpenAndRead()};
  std::array<std::string, 8> comparison = {"000000010", "000000050", "000000090", "000000130", "000000170", "000000210", "000000250", "000000290"};

  EXPECT_EQ(33048, data.size());

  for(size_t it{0}; it < 8; ++it)
  {
    EXPECT_EQ(data[it].GetName(), comparison[it]); 
  }
}
