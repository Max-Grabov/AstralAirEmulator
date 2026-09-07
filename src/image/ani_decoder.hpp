#pragma once

#include "ani.hpp"

#include <cstddef>
#include <optional>
#include <span>

namespace fvp
{

namespace Image
{

[[nodiscard]]
std::optional<Animation> CreateAni(std::span<const std::byte> stream);

}

}
