#pragma once

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include <string_view>

namespace fvp
{

namespace Core
{

class RenderWindow
{
private:
  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};

public:
  RenderWindow(std::string_view window_name, int width_resolution, int height_resolution,
               int window_options = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
  ~RenderWindow();
  RenderWindow(const RenderWindow &) = delete;
  RenderWindow(RenderWindow &&) noexcept;
  RenderWindow &operator=(const RenderWindow &) = delete;
  RenderWindow &operator=(RenderWindow &&) noexcept;

  void RendererPresent();
  SDL_Texture *CreateTexture(SDL_PixelFormat pixel_format, SDL_TextureAccess texture_access_policy,
                             int texture_width, int texture_height);
  bool RenderTexture(SDL_Texture *texture, SDL_FRect *source_rectangle_region,
                     SDL_FRect *destination_rectangle_region);
};
} // namespace Core
} // namespace fvp
