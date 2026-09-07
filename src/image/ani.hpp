#pragma once

#include <cstdint>
#include <vector>

namespace fvp
{

namespace Image
{

class Animation
{
private:
  struct AnimationMetaData
  {
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
  };
  AnimationMetaData meta_data_;
  std::vector<std::vector<std::byte>> frames_;

public:
  Animation(const AnimationMetaData &meta_data, std::vector<std::vector<std::byte>> &&frames);

  const AnimationMetaData &GetMetaData() const;
  const std::vector<std::vector<std::byte>> &GetFrames() const;
};
} // namespace Image
} // namespace fvp
