#include "audio_stream.hpp"
#include "bin.hpp"

#include "decoder.hpp"

#include "gtest/gtest.h"
#include <SDL3/SDL.h>
#include <optional>

TEST(AudioTest, DecodeTest)
{
  using namespace AstralAir::Audio;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/voice.bin");
  bin.OpenAndRead();

  AstralAir::Formats::View voice_view("./AstralAirData/voice.bin");
  std::vector<std::byte> query =
      voice_view.Read(8 + voice_view.Read<uint32_t>(0) * 12 + voice_view.Read<uint32_t>(8), 9);

  auto result = bin.GetChunk(query);
  AudioStream stream = DecodeOggContainer(result);
  EXPECT_EQ(stream.GetChannels(), 1);
  EXPECT_EQ(stream.GetRate(), 48000);
}

TEST(AudioTest, WAVDecodeTest)
{
  using namespace AstralAir::Audio;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/se_sys.bin");
  bin.OpenAndRead();

  AstralAir::Formats::View se_sys_view("./AstralAirData/se_sys.bin");
  std::vector<std::byte> query =
      se_sys_view.Read(8 + se_sys_view.Read<uint32_t>(0) * 12 + se_sys_view.Read<uint32_t>(8), 3);

  std::optional<AudioStream> stream = DecodeWAV(bin.GetChunk(query));

  EXPECT_TRUE(stream);
}
