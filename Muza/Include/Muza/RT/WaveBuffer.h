#pragma once

#include "Muza/RT/BufferBlock.h"
#include "Muza/Types.h"

typedef struct {
  MzBufferBlockZ *activeBlockM;
  MzBufferBlockZ **blocksM;
  MzCountT blocksCountM;
} MzWaveBufferZ;

void MzWaveBufferInitF(MzWaveBufferZ *bufferP, MzCountT blocksCountP,
                       MzFramesT framesCountP, MzChannelsT channelsCountP);

void MzWaveBufferFreeF(MzWaveBufferZ *buffer);
