#include "../../src/formats/bin.hpp"
#include "../../src/data/data.hpp"

#include "gtest/gtest.h"

#include <iostream>

TEST(BinTest, TestOpen)
{
  using AstralAir::Formats::BinFormat;
  using AstralAir::Data::AstralAirData;

  BinFormat bin("./AstralAirData/voice.bin");

  std::vector<AstralAirData> data{bin.OpenAndRead()};
  
  std::cout << data[0].GetData() << "\n";
}
