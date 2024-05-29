#pragma once

#include "Muza/Types.h"

typedef struct {
  MzSampleT *samplesM;
  MzCountT samplesCountM;
  MzFramesT framesCountM;
  MzChannelsT channelsCountM;
} MzBufferBlockZ;

MzBufferBlockZ *MzBufferBlockCreateF(MzFramesT framesCountP,
                                     MzChannelsT channelsCountP);

void MzBufferBlockInitF(MzBufferBlockZ *block, MzFramesT framesCountP,
                        MzChannelsT channelsCountP);

void MzBufferBlockFreeF(MzBufferBlockZ *block);
