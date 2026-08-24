#pragma once

#include <cstdint>
#include <string_view>

namespace fvp
{

namespace Core
{

struct SyscallEntry
{
  uint8_t argument_count;
  uint8_t name_length;
  std::string_view name;
};

} // namespace Core
} // namespace fvp
