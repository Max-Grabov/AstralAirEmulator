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

  std::vector<std::byte> name = {std::byte('0'), std::byte('0'), std::byte('0'),
                                 std::byte('0'), std::byte('0'), std::byte('0'),
                                 std::byte('0'), std::byte('1'), std::byte('0')};

  auto result = bin.GetChunk(name);
  AudioStream stream = DecodeOggContainer(result);
  EXPECT_EQ(stream.GetChannels(), 48000);
}
