#include "bin.hpp"

#include "data.hpp"
#include "decoder.hpp"
#include "audio_playback.hpp"

#include "gtest/gtest.h"
#include <SDL3/SDL.h>

TEST(AudioTest, DecodeTest)
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

