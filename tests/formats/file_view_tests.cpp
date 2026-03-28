#include "../../src/formats/file_view.hpp"

#include "gtest/gtest.h"

#include <cstdint>
#include <string>

TEST(FileViewTest, InvalidPath)
{
  AstralAir::Formats::View view{""};
  EXPECT_FALSE(view.ValidPath());
}

TEST(FileViewTest, ValidPath)
{
  AstralAir::Formats::View view{"./CMakeLists.txt"};
  EXPECT_TRUE(view.ValidPath());
}

TEST(FileViewTest, FileSizeRead)
{
  AstralAir::Formats::View view{"./AstralAirData/voice.bin"};

  EXPECT_TRUE(view.ValidPath());

  // Byte size
  EXPECT_EQ(view.GetFileSize(), 1554116583);
}

TEST(FileViewTest, FileReadUInt8)
{
  AstralAir::Formats::View view{"./AstralAirData/voice.bin"};
  uint64_t test_array[8] = {0b00011000, 0b10000001, 0b00000000, 0b00000000,
                            0b00011011, 0b00001011, 0b00000101, 0b00000000};

  EXPECT_TRUE(view.ValidPath());
  for(uint64_t it{0}; it < 8; ++it)
  {
    EXPECT_EQ(view.Read<uint8_t>(it), test_array[it]);
  }
}

TEST(FileViewTest, FileReadUInt64)
{
  AstralAir::Formats::View view{"./AstralAirData/voice.bin"};
  uint64_t test_array[8] = {0x00050b1b00008118, 0x000b184300000000, 0x0000000a00009941,
                            0x00008ef3000bb184, 0x000c407700000014, 0x0000001e0000b368,
                            0x0000c62a000cf3df, 0x000dba0900000028};

  EXPECT_TRUE(view.ValidPath());

  for(uint64_t it{0}; it < 8; ++it)
  {
    EXPECT_EQ(view.Read<uint64_t>(it), test_array[it]);
  }
}
