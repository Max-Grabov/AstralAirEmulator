#include "file_view.hpp"
#include <cstdio>
#include <iosfwd>
#include <iostream>
#include <sys/stat.h>

namespace AstralAir
{

namespace Formats
{
View::View(const std::string &path)
    : current_offset_(0), file_name_(path), file_data_(path, std::ios::binary)
{
  byte_size_ = GetFileSize();
}

const std::basic_ifstream<uint8_t> &View::GetFileStream() const { return file_data_; }

template <typename T> T View::Read(const uint64_t offset)
{
  T data{0};

  if(current_offset_ + offset > byte_size_)
  {
    std::cerr << "Requested offset will be out of bounds, requested read is position "
              << current_offset_ + offset << "\n";
    return 0;
  }

  if(current_offset_ + offset + static_cast<T>(sizeof(data)) > byte_size_)
  {
    std::cerr << "Requested read will be out of bounds, requested read is positions "
              << current_offset_ + offset << " to " << current_offset_ + offset + sizeof(data)
              << "\n";
    return 0;
  }

  file_data_.seekg(current_offset_ + offset);

  // We set the offset to what our current set offset if plus the parameter
  file_data_.read(reinterpret_cast<std::uint8_t *>(&data), sizeof(data) / sizeof(uint8_t));
  file_data_.seekg(current_offset_);

  return data;
}

uint64_t View::GetFileSize()
{
  struct stat file_stat;
  if(stat(file_name_.c_str(), &file_stat) < 0)
  {
    std::cerr << "Error getting file information for " << file_name_ << "\n";
  }

  return static_cast<uint64_t>(file_stat.st_size);
}
} // namespace Formats

} // namespace AstralAir
