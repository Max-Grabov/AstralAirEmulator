#include "audio_playback.hpp"
#include "audio_stream.hpp"
#include "file_view.hpp"
#include "bin.hpp"
#include "decoder.hpp"
#include <vector>

#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> 

static SDL_AudioStream *bgm_stream = NULL;
static AstralAir::Audio::AudioStream g_bgm_data_stream;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])

{  
  AstralAir::Formats::BinFormat bgm_bin("./AstralAirData/bgm.bin"); 
  AstralAir::Formats::BinFormat voice_bin("./AstralAirData/voice.bin");
 
  bgm_bin.OpenAndRead();
  voice_bin.OpenAndRead();
  

  // For testing, we will read the bgm 0 name from the file so it is easy to query, essentially copying the first part of BinFormat::OpenAndRead() for sample
  AstralAir::Formats::View bgm_view("./AstralAirData/bgm.bin");  
  std::vector<std::byte> query = bgm_view.Read(728, 240);

  auto bgm_data_stream = AstralAir::Audio::DecodeOggContainer(bgm_bin.GetChunk(query));

  if (!SDL_Init(SDL_INIT_AUDIO)) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
  }

  bgm_stream = AstralAir::Audio::CreateAudioStream(bgm_data_stream);
  g_bgm_data_stream = bgm_data_stream;

  if (!bgm_stream) {
      SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
      return SDL_APP_FAILURE;
  }

  SDL_ResumeAudioStreamDevice(bgm_stream);

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
    AstralAir::Audio::PlayAudio(bgm_stream, g_bgm_data_stream);
    played = true;
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{ 
}

