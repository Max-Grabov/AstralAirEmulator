#include <cstdint>
#include <fstream>

namespace AstralAir
{

namespace Formats
{

class View
{
public:
  View(const std::string &path);
  ~View();
  View(View &&other) = default;
  View &operator=(View &&other) = default;

  const std::basic_ifstream<uint8_t> &GetFileStream() const;

  template <typename T> T Read(const uint64_t offset);

  uint64_t GetFileSize();

private:
  uint64_t current_offset_;
  uint64_t byte_size_;
  std::string file_name_;
  std::basic_ifstream<uint8_t> file_data_;
};

} // namespace Formats

} // namespace AstralAir
