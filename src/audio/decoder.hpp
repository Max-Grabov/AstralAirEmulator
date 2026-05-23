#pragma once

#include <audio_stream.hpp>
#include <cstddef>
#include <vector>

namespace AstralAir
{

namespace Audio
{

AudioStream DecodeOggContainer(const std::vector<std::byte> &);

} // namespace Audio
} // namespace AstralAir
