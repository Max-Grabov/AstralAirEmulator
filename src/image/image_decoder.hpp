#pragma once
#include "image.hpp"

#include <vector>
#include <cstddef>
#include <optional>
#include <streambuf>

namespace AstralAir
{

namespace Image
{

class ImageBuf : public std::streambuf
{
public:
  inline ImageBuf(char *begin, char *end) { setg(begin, begin, end); }
  inline ImageBuf() {}
};

std::optional<Image> CreateImage(std::vector<std::byte> &&stream);

}
}
