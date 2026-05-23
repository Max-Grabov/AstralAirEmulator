#include "audio_stream.hpp"
#include "bin.hpp"

#include "decoder.hpp"

#include "gtest/gtest.h"
#include <SDL3/SDL.h>

TEST(AudioTest, DecodeTest)
{
  using namespace AstralAir::Audio;
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/voice.bin");
  bin.OpenAndRead();

  AstralAir::Formats::View voice_view("./AstralAirData/voice.bin");
  std::vector<std::byte> query = voice_view.Read(448624, 278483);

  auto result = bin.GetChunk(query);
  AudioStream stream = DecodeOggContainer(result);
  EXPECT_EQ(stream.GetChannels(), 1);
  EXPECT_EQ(stream.GetRate(), 48000);
}
