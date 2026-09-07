#include "ani.hpp"

namespace fvp
{

namespace Image
{

Animation::Animation(const Animation::AnimationMetaData &meta_data, std::vector<std::vector<std::byte>> &&frames) : meta_data_(meta_data), frames_(std::move(frames)) 
{}

const Animation::AnimationMetaData &Animation::GetMetaData() const { return meta_data_; }

const std::vector<std::vector<std::byte>> &Animation::GetFrames() const { return frames_; }

}

}
