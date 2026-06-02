#pragma once

#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace AstralAir
{

namespace Utility
{

template <typename T> T Get(const std::vector<std::byte> &stream, size_t offset)
{
  static_assert(std::is_standard_layout_v<T> && std::is_trivial_v<T>,
                "Type can't be reinterpret casted");

  if(offset > stream.size())
  {
    throw std::runtime_error("Offset is larger than size");
  }

  if(offset + sizeof(T) > stream.size())
  {
    throw std::runtime_error("Offset + template size is larger than size");
  }

  T data{};

  std::memcpy(&data, stream.data() + offset, sizeof(T));

  return data;
}

template <std::endian E> void ConvertToEndian(std::vector<std::byte> &stream)
{
  if(std::endian::native == E)
    return;
  std::reverse(stream.begin(), stream.end());
}
} // namespace Utility
} // namespace AstralAir
