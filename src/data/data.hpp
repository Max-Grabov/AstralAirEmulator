#include <cstdint>

/**
 * Base virtual class to represent generic Astral Air data parsed from Bin files
 * each Bin file (e.g. bgm, audio, etc) generates different data
 */
namespace AstralAir
{

namespace Data
{
class AstralAirData
{
  uint64_t size_;

public:
  AstralAirData();
  virtual ~AstralAirData();
};

} // namespace Data
} // namespace AstralAir
