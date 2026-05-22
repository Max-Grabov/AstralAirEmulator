#include "audio_playback.hpp"
#include "audio_stream.hpp"
#include "file_view.hpp"
#include "bin.hpp"
#include "data.hpp"
#include "decoder.hpp"

#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> 

static SDL_AudioStream *stream = NULL;
static AstralAir::Audio::AudioStream g_data_stream;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{ 
  AstralAir::Formats::BinFormat bin("./AstralAirData/voice.bin");
  AstralAir::Formats::View data_view("./AstralAirData/voice.bin");

  std::vector<AstralAir::Data::AstralAirData> data{bin.OpenAndRead()};
  auto offset = data[5].GetOffset();
  auto size = data[5].GetData();
  auto result = data_view.Read(offset, size);
  auto data_stream = AstralAir::Audio::DecodeOggContainer(data_view.Read(offset, size));
  SDL_AudioSpec spec;

  if (!SDL_Init(SDL_INIT_AUDIO)) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
  }

  stream = AstralAir::Audio::CreateAudioStream(data_stream);
  g_data_stream = data_stream;

  if (!stream) {
      SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
      return SDL_APP_FAILURE;
  }

  SDL_ResumeAudioStreamDevice(stream);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; 
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{ 
  static bool played{false};

  if(!played)
  {
    AstralAir::Audio::PlayAudio(stream, g_data_stream); 
    played = true;
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{ 
}

