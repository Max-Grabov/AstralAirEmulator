#include "decoder.hpp"
#include "vorbis/codec.h"
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ogg/config_types.h>
#include <ogg/ogg.h>

// Ogg Stream decoding taken and adapted from this example here -> https://github.com/xiph/vorbis/blob/main/examples/decoder_example.c

namespace AstralAir
{

namespace Audio
{

void DecodeOggContainer(const std::vector<std::byte> &input_buffer)
{
  ogg_sync_state sync_state;
  ogg_stream_state stream_state;
  ogg_page ogg_page;
  ogg_packet ogg_packet;
  vorbis_info v_info;
  vorbis_comment v_comment;
  vorbis_dsp_state v_dsp;
  vorbis_block v_block;
  bool stream_end{false};

  ogg_sync_init(&sync_state);

  if(input_buffer.size() == 0)
  {
    std::cerr << "Input stream for decoding is empty\n";

    // Return an empty whatever once return type is decided
    return;
  }

  long byte_size = input_buffer.size();

  // Add one for null terminator when moving the input_buffer's data to the buffer
  char *buffer = ogg_sync_buffer(&sync_state, byte_size);

  if(!buffer)
  {
    std::cerr << "Input buffer for decoding is empty\n";
    return;
  }

  std::memcpy(buffer, input_buffer.data(), byte_size);

  ogg_sync_wrote(&sync_state, byte_size);

  if(ogg_sync_pageout(&sync_state, &ogg_page) != 1)
  {
    std::cerr << "Error with sync pageout\n";
    return;
  }

  ogg_stream_init(&stream_state, ogg_page_serialno(&ogg_page));
  vorbis_info_init(&v_info);
  vorbis_comment_init(&v_comment);

  // Standard check to ensure it is vorbis
  if(ogg_stream_pagein(&stream_state, &ogg_page) < 0)
  {
    std::cerr << "Error reading first page of OggStream\n";
    std::cout << ogg_page_version(&ogg_page) << "\n";
    std::cout << ogg_page_serialno(&ogg_page) << "\n";
    std::cout << stream_state.serialno << "\n";

    return;
  }
  if(ogg_stream_packetout(&stream_state, &ogg_packet) != 1)
  {
    std::cerr << "Error reading initial packet of OggStream\n";
    return;
  }
  if(vorbis_synthesis_headerin(&v_info, &v_comment, &ogg_packet) < 0)
  {
    std::cerr << "OggStream has no vorbis data\n";
    return;
  }

  // First two packets
  for(uint8_t count{}; count < 2;)
  {
    if(!ogg_sync_pageout(&sync_state, &ogg_page))
    {
      std::cout << "empty\n";
      break;
    }

    ogg_stream_pagein(&stream_state, &ogg_page);
    while(count < 2)
    {
      auto result = ogg_stream_packetout(&stream_state, &ogg_packet);
      if(!result)
      {
        std::cout << "empty\n";
        break;
      }
      if(result < 0)
      {
        std::cerr << "Corrupted\n";
        return;
      }
      result = vorbis_synthesis_headerin(&v_info, &v_comment, &ogg_packet);
      if(result < 0)
      {
        std::cerr << "Corrupted\n";
        return;
      }
      ++count;
    }
  }

  char **pin = v_comment.user_comments;
  while(*pin)
  {
    std::cout << *pin << "\n";++pin;
  }
  std::cout << "channel " << v_info.channels << " rate " << v_info.rate << "\n";
      
  int conv_size = byte_size / v_info.channels;

  // From the example, we should have parsed the three headers. Now we can initialize the vorbis packet
  if(vorbis_synthesis_init(&v_dsp, &v_info) == 0)
  {
    vorbis_block_init(&v_dsp, &v_block);

    // Now we should be able to decode until end of stream
    bool end_of_stream{false};
    while(!end_of_stream)
    {
      auto result = ogg_sync_pageout(&sync_state, &ogg_page);
      if(!result) break;
      if(result < 0)
      {
        std::cerr << "Corrupted\n";
        return;
      }
      else
      {
        ogg_stream_pagein(&stream_state, &ogg_page);
        while(1)
        {
          auto second_result = ogg_stream_packetout(&stream_state, &ogg_packet); 
          if(!second_result) break;
          if(second_result < 0)
          {
            std::cerr << "Corrupted\n";
            return;    
          }
          else
          {
            float **pcm;
            int samples;
            std::vector<ogg_uint16_t> pcm_output;

            if(vorbis_synthesis(&v_block, &ogg_packet) == 0)
              vorbis_synthesis_blockin(&v_dsp, &v_block);
            
            while((samples = vorbis_synthesis_pcmout(&v_dsp, &pcm)) > 0)
            {
              bool clipflag{false};
              int bout = std::min(samples, conv_size); 
              pcm_output.reserve(bout * v_info.channels);

              for(int i{}; i < v_info.channels; i++)
              { 
                for(int j{}; j < bout; j++)
                {
                  float sample = pcm[i][j];
                  int value = std::floor(sample * 32767.0f + 0.5f);
                  value = std::clamp(value, -32768, 32677);
                  pcm_output.push_back(static_cast<int16_t>(value));
                }
              }

              if(clipflag)
                std::cerr << "Clipping at frame " << v_dsp.sequence << "\n";   

              vorbis_synthesis_read(&v_dsp, bout);
            }
          }
        }
        if(ogg_page_eos(&ogg_page)) end_of_stream = 1;
      }
    }
    // Stream should be over
    vorbis_block_clear(&v_block);
    vorbis_dsp_clear(&v_dsp);
  }
  else
  {
    std::cerr << "Corrupt Header\n";
  }

  ogg_stream_clear(&stream_state);
  vorbis_comment_clear(&v_comment);
  vorbis_info_clear(&v_info);

  ogg_sync_clear(&sync_state);
}

} // namespace Audio
} // namespace AstralAir
