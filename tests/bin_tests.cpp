#include "bin.hpp"
#include "gtest/gtest.h"

TEST(BinTest, TestOpen)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;

  BinFormat bin("./AstralAirData/voice.bin");
  bin.OpenAndRead();

  // In a real scenario, we wouldn't need to set up another view to the same file to query. this is done since I don't have access/dont remember any data names, so we just grab on at the offset to use as the test query
  AstralAir::Formats::View voice_view("./AstralAirData/voice.bin");
  std::vector<std::byte> query = voice_view.Read(8 + voice_view.Read<uint32_t>(0) * 12 + voice_view.Read<uint32_t>(8), 9);

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
  std::vector<std::byte> query = voice_view.Read(8 + voice_view.Read<uint32_t>(0) * 12 + voice_view.Read<uint32_t>(8), 9);

  auto result = bin.GetChunk(query);

  EXPECT_EQ(static_cast<char>(result[0]), 'O');
  EXPECT_EQ(static_cast<char>(result[1]), 'g');
  EXPECT_EQ(static_cast<char>(result[2]), 'g');
  EXPECT_EQ(static_cast<char>(result[3]), 'S');
}

TEST(BinTest, TestImageRead)
{
  using AstralAir::Data::AstralAirData;
  using AstralAir::Formats::BinFormat;
  using AstralAir::Formats::View;

  BinFormat bin("./AstralAirData/graph_vis.bin");
  bin.OpenAndRead(); 

  AstralAir::Formats::View g_view("./AstralAirData/graph_vis.bin");
  std::vector<std::byte> query = g_view.Read(8 + g_view.Read<uint32_t>(0) * 12 + g_view.Read<uint32_t>(8), 9); 

  EXPECT_TRUE(bin.HasEntry(query));
}
