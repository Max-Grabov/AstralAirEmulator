#include <cstdint>
#include <fstream>

namespace AstralAir
{

namespace Formats
{

class View
{
public:
  View(const std::string &);
  ~View();
  View(View &&) = default;
  View &operator=(View &&) = default;

  const std::ifstream &GetFileStream() const;

  template <typename T> T Read(const uint64_t);

  uint64_t GetFileSize() const;
  bool ValidPath() const;

private:
  static constexpr uint8_t OFFSET_CONVERSION_{8};
  uint64_t current_offset_;
  uint64_t byte_size_;
  std::string file_name_;
  std::ifstream file_data_;
};

} // namespace Formats

} // namespace AstralAir
