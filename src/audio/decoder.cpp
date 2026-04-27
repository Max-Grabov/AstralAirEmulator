#include "decoder.hpp"
#include "vorbis/codec.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <ogg/ogg.h>

namespace AstralAir
{

namespace Audio
{

OggStreamInfo::OggStreamInfo()
{
  
}

OggStreamInfo::~OggStreamInfo()
{
  ogg_stream_clear(&stream_state);
  ogg_sync_clear(&sync_state);
}

void DecodeOggContainer(const std::string &view)
{
  OggStreamInfo ogg_stream;
  ogg_page ogg_page;
  ogg_packet ogg_packet;
  vorbis_info v_info;
  vorbis_comment v_comment;
  vorbis_dsp_state v_dsp;
  vorbis_block v_block;
  bool stream_end{false};

  while(1)
  {
    // First thing we want to do is determine the size of the stream, each character in our string view is 1 byte so it is trivial to do so.
    if(view.size() == 0)
    {
      std::cerr << "Input stream for decoding is empty\n";

      // Return an empty whatever once return type is decided
      return;
    }

    long byte_size = view.size() * sizeof(char);
    char *buffer = ogg_sync_buffer(&ogg_stream.sync_state, byte_size);

    if(!buffer)
    {
      std::cerr << "Input buffer for decoding is empty\n";
      return;
    }

    if(ogg_sync_pageout(&ogg_stream.sync_state, &ogg_page) != 1)
    {
      if(byte_size < (0b1 << 12))
      {
        // out of data
        break;
      }
    }
    
    ogg_sync_wrote(&ogg_stream.sync_state, byte_size);
    ogg_stream_init(&ogg_stream.stream_state, ogg_page_serialno(&ogg_page));
    
    vorbis_info_init(&v_info);
    vorbis_comment_init(&v_comment);

    // Standard check to ensure it is vorbis
    if(ogg_stream_pagein(&ogg_stream.stream_state, &ogg_page) < 0)
    {
      std::cerr << "Error reading first page of OggStream\n";
      return;
    }
    if(ogg_stream_packetout(&ogg_stream.stream_state, &ogg_packet) != 1)
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
      if(!ogg_sync_pageout(&ogg_stream.sync_state, &ogg_page)) break;

      ogg_stream_pagein(&ogg_stream.stream_state, &ogg_page);
      while(count < 2)
      {
        auto result = ogg_stream_packetout(&ogg_stream.stream_state, &ogg_packet);
        if(!result) break;
        if(result < 0)
        {
          // Corrupted
          return;
        }
        result=vorbis_synthesis_headerin(&v_info, &v_comment, &ogg_packet);
        if(result < 0)
        {
          // Corrupted
          return;
        }
        ++count;
      } 
    }

    {
      char **pin = v_comment.user_comments;
      while(*pin) std::cout << *pin << "\n"; ++pin;
    }
  }
}

}
}
