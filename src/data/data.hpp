#include <cstddef>
#include <cstdint>
#include <vector>

namespace AstralAir
{

namespace Data
{
struct AstralAirData
{
private:
  std::vector<std::byte> name_;
  uint32_t offset_;
  uint32_t data_;

public:
  AstralAirData(const std::vector<std::byte> &buffer, uint32_t offset, uint32_t data)
      : name_(buffer), offset_(offset), data_(data)
  {
  }
  const std::vector<std::byte> &GetName() const { return name_; }
  const uint32_t GetOffset() const { return offset_; }
  const uint32_t GetData() const { return data_; }
};

} // namespace Data
} // namespace AstralAir
