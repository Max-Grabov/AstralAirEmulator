#include "decoder.hpp"
#include "data.hpp"
#include "bin.hpp"

#include "gtest/gtest.h"

TEST(DecoderTest, DecodeTest)
{ 
  using namespace AstralAir::Audio;
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;

  BinFormat bin("./AstralAirData/voice.bin");

  std::vector<AstralAirData> data{bin.OpenAndRead()}; 
  DecodeOggContainer(data[8456].GetName()); 
}
