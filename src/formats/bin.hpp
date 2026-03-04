
#include <string>
#include <cstdint>
#include <vector>
#include <filesystem>
#include "data/data.hpp"

namespace AstralAir
{

using fs = std::filesystem;
namespace Formats
{

class BinFormat
{
  std::string extension_;
  std::string file_name_;
  uint64_t byte_size_;
  uint64_t current_offset_;
  fs path_;

  BinFormat(const std::string &extension, const std::string &file_name_);
  ~BinFormat() = default;
  BinFormat(const BinFormat& other) = default;
  BinFormat(BinFormat&& other) = default;
  BinFormat& operator=(const BinFormat &other) = default; 
  BinFormat& operator=(BinFormat &&other) = default;

  public std::vector<Data::AstralAirData> Open(); 
  
};

} 
}
