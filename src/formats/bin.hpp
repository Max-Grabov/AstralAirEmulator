
#include <cstdint>
#include <filesystem>
#include <map>
#include <memory>
#include <string>

namespace AstralAir
{

namespace Data
{
class AstralAirData;
}

namespace Formats
{

namespace fs = std::filesystem;

class BinFormat
{
  uint64_t current_offset_;
  uint64_t byte_size_;
  std::string extension_;
  std::string file_name_;
  fs::path path_;

public:
  BinFormat();
  virtual ~BinFormat() = default;
  BinFormat(const BinFormat &other) = default;
  BinFormat(BinFormat &&other) = default;
  BinFormat &operator=(const BinFormat &other) = default;
  BinFormat &operator=(BinFormat &&other) = default;

  virtual std::map<uint64_t, std::unique_ptr<Data::AstralAirData>> Open() = 0;
};

} // namespace Formats

} // namespace AstralAir
