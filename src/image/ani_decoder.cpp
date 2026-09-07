#include "ani_decoder.hpp"
#include "util/file/binary_stream_util.hpp"

#include <cstdint>
namespace fvp
{

namespace Image
{

std::optional<Animation> CreateAni(std::span<const std::byte> stream)
{

// RIFF Chunk
  if(stream.size() < 12)
  {
    return std::nullopt;
  }

  if(uint32_t id{Utility::Get<uint32_t, std::endian::little>(stream, 0)}; id != 0x52494646)
  {
    return std::nullopt;
  }

  uint32_t size{Utility::Get<uint32_t, std::endian::big>(stream, 4)};
  if(stream.size() != size)
  {
    return std::nullopt;
  }

  if(uint32_t type{Utility::Get<uint32_t, std::endian::little>(stream, 8)}; type != 0x41434f4e)
  {
    return std::nullopt;
  }

  return Animation({}, {});
}

}

}
