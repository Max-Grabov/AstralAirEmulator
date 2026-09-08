#pragma once

#include "SDL3/SDL_mouse.h"
#include <span>
#include <cstddef>

namespace fvp
{

namespace Core
{

class Cursor
{
private:
  SDL_Cursor * cursor_{nullptr};
  
public:
  Cursor(const std::span<const std::byte> ani_data, int click_x = 0, int click_y = 0);
  ~Cursor();
  void SetCursor() const;
};
}
}
