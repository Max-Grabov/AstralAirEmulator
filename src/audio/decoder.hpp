#include <ogg/ogg.h>
#include <string>
namespace AstralAir
{

namespace Audio
{

struct OggStreamInfo
{
  ogg_sync_state sync_state; 
  ogg_stream_state stream_state;

  OggStreamInfo();
  ~OggStreamInfo();
};

void DecodeOggContainer(const std::string &view);

} // namespace Audio
} // namespace AstralAir
