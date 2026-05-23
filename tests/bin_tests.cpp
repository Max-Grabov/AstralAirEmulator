#include "bin.hpp"
#include "gtest/gtest.h"

TEST(BinTest, TestOpen)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;

  BinFormat bin("./AstralAirData/voice.bin");
  bin.OpenAndRead();

  AstralAir::Formats::View voice_view("./AstralAirData/voice.bin");
  std::vector<std::byte> query = voice_view.Read(448624, 278483);

  EXPECT_EQ(33048, bin.CollectionSize());
  EXPECT_TRUE(bin.HasEntry(query));
}

TEST(BinTest, TestDataReadHeader)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/voice.bin");
  bin.OpenAndRead();

  AstralAir::Formats::View voice_view("./AstralAirData/voice.bin");
  std::vector<std::byte> query = voice_view.Read(448624, 278483);

  auto result = bin.GetChunk(query);

  EXPECT_EQ(static_cast<char>(result[0]), 'O');
  EXPECT_EQ(static_cast<char>(result[1]), 'g');
  EXPECT_EQ(static_cast<char>(result[2]), 'g');
  EXPECT_EQ(static_cast<char>(result[3]), 'S');
}
