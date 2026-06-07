#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

#include "zstr.hpp"

#include "binary_stream_util.hpp"
#include "hzc_stream.hpp"

namespace AstralAir
{

namespace Image
{
  
class Image
{
private:
  struct ImageMetaData
  {
    uint16_t type;
    uint16_t width;
    uint16_t height;
    uint16_t offset_x;
    uint16_t offset_y;
    uint16_t bpp;
    uint32_t unpacked_size;
    uint32_t header_size;
  };
  ImageMetaData meta_data_;
  std::vector<char> pixels_;
public:
  Image(ImageMetaData meta_data, std::vector<char> &&pixels) : meta_data_(meta_data), pixels_(std::move(pixels)) {}
  inline void PrintImageMetaData() const 
  {
    auto print_all = [](const auto &...params) { ((std::cout << params << "\n"), ...); };
    print_all(meta_data_.unpacked_size, meta_data_.header_size, meta_data_.type, meta_data_.width,
              meta_data_.height, meta_data_.offset_x, meta_data_.offset_y, meta_data_.bpp);
  }
  inline const ImageMetaData &GetMetaData() const { return meta_data_; } 
  inline const std::vector<char> &GetPixels() const { return pixels_; }
};

Image CreateImage(const HZC_Stream &hzc_stream)
{
  // Metadata Information
  const std::vector<std::byte> &stream = hzc_stream.GetStream();
  uint32_t unpacked_size = Utility::Get<uint32_t>(stream, 4);
  uint32_t header_size = Utility::Get<uint32_t>(stream, 8);
  uint16_t type = Utility::Get<uint16_t>(stream, 18);
  uint16_t width = Utility::Get<uint16_t>(stream, 20);
  uint16_t height = Utility::Get<uint16_t>(stream, 22);
  uint16_t offset_x = Utility::Get<uint16_t>(stream, 24);
  uint16_t offset_y = Utility::Get<uint16_t>(stream, 26);
  uint16_t bpp = 0 == type ? 24 : type > 2 ? 8 : 32;

  zstr::istream * const z_stream = hzc_stream.GetZlibStream();
  std::vector<char> pixels(unpacked_size);

  z_stream->read(pixels.data(), unpacked_size);
  return {{type, width, height, offset_x, offset_y, bpp, unpacked_size, header_size}, std::move(pixels)};
}
}
}
