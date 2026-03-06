
#include <string>
#include <cstdint>
#include <map>
#include <filesystem>

namespace AstralAir
{

namespace Data { class AstralAirData; }

namespace Formats
{

namespace fs = std::filesystem;

class BinFormat
{
  std::string extension_;
  std::string file_name_;
  uint64_t byte_size_;
  uint64_t current_offset_;
  fs::path path_;

  BinFormat(const std::string &path_);
  ~BinFormat() = default;
  BinFormat(const BinFormat& other) = default;
  BinFormat(BinFormat&& other) = default;
  BinFormat& operator=(const BinFormat &other) = default; 
  BinFormat& operator=(BinFormat &&other) = default;

  virtual std::map<uint64_t, Data::AstralAirData> Open() = 0; 
  
};

} 
}
