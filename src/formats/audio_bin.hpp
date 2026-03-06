#include "bin.hpp"

namespace AstralAir
{

namespace Data { class AudioEntry; }

namespace Formats
{

class AudioBin : public BinFormat
{
  AudioBin(const std::string &path); 
  ~AudioBin();
  AudioBin(const AudioBin& other) = default;
  AudioBin(AudioBin&& other) = default;
  AudioBin& operator=(const AudioBin &other) = default; 
  AudioBin& operator=(AudioBin &&other) = default;

  std::map<uint64_t, std::unique_ptr<Data::AstralAirData>> Open(); 
};

}

}
