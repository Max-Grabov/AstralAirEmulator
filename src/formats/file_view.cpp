#include "file_view.hpp"

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <type_traits>

namespace AstralAir
{

namespace Formats
{
View::View(const std::string &path)
    : current_offset_(0), file_name_(path), file_data_(path, std::ios::binary)
{
  byte_size_ = GetFileSize();
}

View::~View() { file_data_.close(); }

const std::ifstream &View::GetFileStream() const { return file_data_; }

template <typename T> T View::Read(const uint64_t offset)
{
  static_assert(std::is_standard_layout_v<T> && std::is_trivial_v<T>,
                "Type can't be reinterpret casted");

  if(!ValidPath())
  {
    return 0;
  }

  T data{0};

  if(sizeof(T) * (current_offset_ + offset) > byte_size_)
  {
    std::cerr << "Requested offset will be out of bounds, requested read is byte "
              << current_offset_ + offset << "\n";
    return 0;
  }

  if(sizeof(T) * (current_offset_ + offset + static_cast<T>(sizeof(T))) > byte_size_)
  {
    std::cerr << "Requested read will be out of bounds, requested read is bytes "
              << current_offset_ + offset << " to " << current_offset_ + offset + sizeof(T) << "\n";
    return 0;
  }

  // We set the offset to what our current set offset is plus the parameter
  // Conversion is needed if our data type is bigger than 1 byte, as seekg offset acts as one byte
  // (e.g. uint64_t offset value of corresponds to an actual uint64_t 8 byte offset, whereas uint8_t
  // offset value should just be 1 byte per offset value)
  // TODO this needs to get thought out more (e.g. remove current_offset_)
  file_data_.seekg(sizeof(T) * (current_offset_ + offset), std::ios::beg);

  // This must be char *, uint8_t is not guarranteed to play nice (e.g. in testing all reads were
  // returning 0)
  file_data_.read(reinterpret_cast<char *>(&data), sizeof(T));
  file_data_.seekg(current_offset_, std::ios::beg);

  return data;
}

uint64_t View::GetFileSize() const
{

  if(!ValidPath())
  {
    return 0;
  }

  struct stat file_stat;
  if(stat(file_name_.c_str(), &file_stat) < 0)
  {
    std::cerr << "Error getting file information for " << file_name_ << "\n";
    return 0;
  }

  return static_cast<uint64_t>(file_stat.st_size);
}

bool View::ValidPath() const { return file_data_.is_open(); }

template uint8_t View::Read<uint8_t>(const uint64_t);
template uint32_t View::Read<uint32_t>(const uint64_t);
template uint64_t View::Read<uint64_t>(const uint64_t);

} // namespace Formats

} // namespace AstralAir
