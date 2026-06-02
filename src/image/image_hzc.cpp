
#include "image_hzc.hpp"
#include "binary_stream_util.hpp"
#include <cstdint>

namespace AstralAir
{

namespace Image
{

void HZC_Format::OpenAndReadMetaData()
{
  // We impose that the std::vector is a valid stream. This means that atleast the first 3
  // characters should be 'hzc' Also, we impose that the size of the vector stream is enough for the
  // metadata. (this is done in Get function)
  // TODO
  MetaData meta_data;
  meta_data.type = Utility::Get<uint16_t>(stream_, 18);
  meta_data.width = Utility::Get<uint16_t>(stream_, 20);
  meta_data.height = Utility::Get<uint16_t>(stream_, 22);
  meta_data.offset_x = Utility::Get<uint16_t>(stream_, 24);
  meta_data.offset_y = Utility::Get<uint16_t>(stream_, 26);
  meta_data.unpacked_size = Utility::Get<uint32_t>(stream_, 4);
  meta_data.header_size = Utility::Get<uint32_t>(stream_, 8);
}
} // namespace Image
} // namespace AstralAir
