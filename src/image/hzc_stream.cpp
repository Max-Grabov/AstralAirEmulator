#include "hzc_stream.hpp"
#include "binary_stream_util.hpp"

#include <cstdint>
#include <memory>

namespace AstralAir
{

namespace Image
{

void HZC_Stream::PrepareZlibStream()
{
  uint32_t header_size = Utility::Get<uint32_t>(stream_, 8);
  uint32_t position{12 + header_size};
  view_ = std::make_unique<ImageBuf>(reinterpret_cast<char *>(stream_.data()) + position,
                                     reinterpret_cast<char *>(stream_.data()) + stream_.size());
  zlib_stream_ = std::make_unique<zstr::istream>(view_.get());
}
} // namespace Image
} // namespace AstralAir
