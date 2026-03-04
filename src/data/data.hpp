#include <string>

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
public:
  AstralAirData(); 
  virtual ~AstralAirData() = 0;
private:

};
}
}
