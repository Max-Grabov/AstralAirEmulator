#include <cstdint>
#include <string>

namespace AstralAir
{

namespace Data
{
struct AstralAirData
{
private:
  std::string data_name_;
  uint32_t offset_;
  uint32_t data_;

public:
  AstralAirData(const std::string &, uint32_t, uint32_t);

  const std::string &GetName() const { return data_name_; }
  const uint32_t GetOffset() const { return offset_; }
  const uint32_t GetData() const { return data_; }
};

} // namespace Data
} // namespace AstralAir
