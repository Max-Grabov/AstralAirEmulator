#pragma once

#include <cstddef>
#include <vector>
#include <audio_stream.hpp>

namespace AstralAir
{

namespace Audio
{

AudioStream DecodeOggContainer(const std::vector<std::byte> &);

} // namespace Audio
} // namespace AstralAir
