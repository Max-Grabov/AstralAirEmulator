#pragma once

#include <vector>

namespace AstralAir
{

namespace Audio
{
class AudioStream
{
private:
  std::vector<float> stream_;
  long channels_;
  long rate_;

public:
  AudioStream(std::vector<float> &, long, long);
  AudioStream(std::vector<float> &&, long, long);
  AudioStream();
  const std::vector<float> &GetStream() const { return stream_; }
  long GetChannels() const { return channels_; }
  long GetRate() const { return rate_; }
};
} // namespace Audio
} // namespace AstralAir
