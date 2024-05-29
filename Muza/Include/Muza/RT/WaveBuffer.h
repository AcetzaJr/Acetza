#pragma once

#include "Muza/RT/BufferBlock.h"
#include "Muza/Types.h"

typedef struct {
  MzBufferBlockZ *activeBlockM;
  MzBufferBlockZ **blocksM;
  MzCountT blocksCountM;
  MzIndexT sampleIndexM;
} MzWaveBufferZ;

void MzWaveBufferInitF(MzWaveBufferZ *bufferP, MzCountT blocksCountP,
                       MzFramesT framesCountP, MzChannelsT channelsCountP);

void MzWaveBufferFreeF(MzWaveBufferZ *bufferP);

double MzWaveBufferNextSampleF(MzWaveBufferZ *bufferP);

bool MzWaveBufferTrySwapF(MzWaveBufferZ *bufferP);
