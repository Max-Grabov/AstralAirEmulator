#include "bin.hpp"
#include "data.hpp"
#include "decoder.hpp"

#include "gtest/gtest.h"

TEST(DecoderTest, DecodeTest)
{
  using namespace AstralAir::Audio;
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/voice.bin");
  View data_view("./AstralAirData/voice.bin");
  
  std::vector<AstralAirData> data{bin.OpenAndRead()};
  auto offset = data[0].GetOffset();
  auto size = data[0].GetData();
  auto result = data_view.Read(offset, size);
  DecodeOggContainer(data_view.Read(offset, size));
}
