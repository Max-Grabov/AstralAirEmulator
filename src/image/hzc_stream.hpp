#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "zstr.hpp"

#include "binary_stream_util.hpp"

template <class T>
concept Constructable = std::is_move_constructible_v<T> &&
                        std::convertible_to<std::vector<std::byte>, T> && requires(T t) {
                          { t.size() } -> std::convertible_to<size_t>;
                        };

namespace AstralAir
{

namespace Image
{

class HZC_Stream
{
private:
  class ImageBuf : public std::streambuf
  {
  public:
    inline ImageBuf(char *begin, char *end) { setg(begin, begin, end); }
    inline ImageBuf() {}
  };

  std::vector<std::byte> stream_;
  std::unique_ptr<ImageBuf> view_{nullptr};
  std::shared_ptr<zstr::istream> zlib_stream_{nullptr};
  
  template <typename T> HZC_Stream(T &&stream) : stream_(std::forward<T>(stream))
  {
    PrepareZlibStream();
  }
  void PrepareZlibStream();

public:
  template <Constructable T> static std::optional<HZC_Stream> Construct(T &&stream)
  {
    // Check some obvious conditions
    // Metadata at a minimum 28 bytes
    if(stream.size() < 28)
    {
      return std::nullopt;
    }

    // All Streams should start with these 4 bytes (big endian representing 'hzc1')
    if(Utility::Get<uint32_t>(stream, 0) == 0x3d637a68)
    {
      return std::nullopt;
    }

    // At the position 12 + header_size is where the zlib header is located, this must be divisible by 31 and is stored as a little endian
    // 78 01
    // 78 5E
    // 78 9C
    // 78 DA
    uint32_t zlib_header{Utility::Get<uint32_t>(stream, Utility::Get<uint32_t>(stream, 8) + 12)};
    Utility::ConvertToEndian<std::endian::little, uint32_t>(zlib_header);
    if((zlib_header % 31) != 0)
    {
      return std::nullopt; 
    }

    return HZC_Stream(std::forward<T>(stream));
  }

  ~HZC_Stream() = default;
  HZC_Stream(const HZC_Stream &other) = delete;
  HZC_Stream &operator=(const HZC_Stream &other) = delete;
  HZC_Stream(HZC_Stream &&other) = default;
  HZC_Stream &operator=(HZC_Stream &&other) = default;
  inline zstr::istream * const GetZlibStream() const
  {
    return zlib_stream_.get(); 
  }
  inline const std::vector<std::byte> & GetStream() const
  {
    return stream_;
  }
};

} // namespace Image

} // namespace AstralAir
