#include <cstdint>
#include <vector>

namespace AstralAir
{

namespace Audio
{
class AudioStream
{
private:
  std::vector<uint16_t> stream_;
  uint32_t channels_;
  uint32_t rate_;

public:
  AudioStream(std::vector<uint16_t> &, uint32_t, uint32_t);
  AudioStream(std::vector<uint16_t> &&, uint32_t, uint32_t);
  const std::vector<uint16_t> &GetStream() const { return stream_; }
  uint32_t GetChannels() const { return channels_; }
  uint32_t GetRate() const { return rate_; }
};
} // namespace Audio
} // namespace AstralAir
