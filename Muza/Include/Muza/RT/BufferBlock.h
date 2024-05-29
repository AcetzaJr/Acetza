#pragma once

#include "Muza/Types.h"

typedef struct {
  MzSampleT *samplesM;
  MzCountT samplesCountM;
  MzFramesT framesCountM;
  MzChannelsT channelsCountM;
  bool isReadyM;
} MzBufferBlockZ;

MzBufferBlockZ *MzBufferBlockCreateF(MzFramesT framesCountP,
                                     MzChannelsT channelsCountP);

void MzBufferBlockInitF(MzBufferBlockZ *block, MzFramesT framesCountP,
                        MzChannelsT channelsCountP);

void MzBufferBlockFreeF(MzBufferBlockZ *block);

void MzBufferBlockNotReadyF(MzBufferBlockZ *block);
