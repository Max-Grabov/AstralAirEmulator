#include "cursor.hpp"
#include "SDL3/SDL_iostream.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3_image/SDL_image.h"
#include <span>
#include <cstddef>
#include <stdexcept>

namespace fvp
{

namespace Core
{

Cursor::Cursor(const std::span<const std::byte> ani_data, int click_x, int click_y)
{
  SDL_IOStream * io_stream = SDL_IOFromConstMem(ani_data.data(), ani_data.size()); 

  if(!io_stream)
  {
    throw std::runtime_error("invalid io");
  }

  IMG_Animation * animation = IMG_LoadANIAnimation_IO(io_stream);
  SDL_CloseIO(io_stream);

  if(!animation)
  {
    throw std::runtime_error("No animation");
  }

  cursor_ = IMG_CreateAnimatedCursor(animation, click_x, click_y); 
  if(!cursor_)
  {
    throw std::runtime_error("No cursor");
  }

  IMG_FreeAnimation(animation);
}

Cursor::Cursor(SDL_Cursor * cursor) : cursor_(cursor)
{
  if(!cursor_)
  {
    throw std::runtime_error("Attempting to set an Cursor from null SDL Cursor");
  }
} 

Cursor::~Cursor()
{
  SDL_DestroyCursor(cursor_);
}

void Cursor::SetCursor() const
{
  // TODO something
  if(!SDL_SetCursor(cursor_))
  {
  };
}

}
}
