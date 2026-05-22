#pragma once
#include "audio_stream.hpp"
#include <functional>

#include <SDL3/SDL_audio.h>

namespace AstralAir
{

namespace Audio
{

SDL_AudioStream * CreateAudioStream(const AudioStream &);

void PlayAudio(SDL_AudioStream *, const AudioStream &, const std::function<void(SDL_AudioStream *, const AudioStream &)> & = nullptr);

}
}
