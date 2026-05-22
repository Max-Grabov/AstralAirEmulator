
#include "bin.hpp"
#include "data.hpp"

#include <cstdint>
#include <filesystem>

// File decoding for the binary files is heavily based on
// https://github.com/morkt/GARbro/blob/master/ArcFormats/Favorite/ArcBIN.cs
// As these goats figured out the way to decode the binary files.
namespace AstralAir
{

namespace Formats
{

BinFormat::BinFormat(const std::string &path) : file_view_(path)
{
  // We assume the files are exactly the proper data files, there should be proper checks before
  // reading more
  count_ = file_view_.Read<uint32_t>(0);
  index_size_ = count_ * 12;

  name_index_size_ = file_view_.Read<uint32_t>(4);

  if(std::filesystem::path(path).filename() == "voice")
  {
    file_type_ = FileType::VOICE;
  }
  else if(std::filesystem::path(path).filename() == "bgm")
  {
    file_type_ = FileType::BGM;
  }
  // TODO MORE
}

std::vector<Data::AstralAirData> BinFormat::OpenAndRead()
{
  std::vector<Data::AstralAirData> data_collection;
  uint32_t file_offset{8};
  uint64_t names_base_position{file_offset + index_size_};
  for(int i = 0; i < count_; ++i)
  {
    uint32_t filename_offset{file_view_.Read<uint32_t>(file_offset)};
    if(filename_offset >= name_index_size_)
      return data_collection;

    std::vector<std::byte> name_buffer{
        file_view_.Read(names_base_position + filename_offset, name_index_size_ - filename_offset)};
    uint32_t offset{file_view_.Read<uint32_t>(file_offset + 4)};
    uint32_t data{file_view_.Read<uint32_t>(file_offset + 8)};
    data_collection.emplace_back(std::move(name_buffer), offset, data);
    file_offset += 12;
  }

  return data_collection;
}

} // namespace Formats
} // namespace AstralAir
