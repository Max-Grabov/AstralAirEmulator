#include "bin.hpp"

namespace AstralAir
{

namespace Data
{
class AudioEntry;
}

namespace Formats
{

class AudioBin : public BinFormat
{
public:
  AudioBin(const std::string &);
  ~AudioBin();
  AudioBin(const AudioBin &) = default;
  AudioBin(AudioBin &&) = default;
  AudioBin &operator=(const AudioBin &) = default;
  AudioBin &operator=(AudioBin &&) = default;

  std::map<uint64_t, std::unique_ptr<Data::AstralAirData>> Open();
};

} // namespace Formats

} // namespace AstralAir
