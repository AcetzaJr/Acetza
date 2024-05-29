#include "Muza/RT/BufferBlock.h"

#include "Muza/Panic.h"
#include "Muza/Types.h"

#include <stdlib.h>

MzBufferBlockZ *MzBufferBlockCreateF(MzFramesT framesCountP,
                                     MzChannelsT channelsCountP) {
  MzBufferBlockZ *block = malloc(sizeof(MzBufferBlockZ));
  if (block == NULL) {
    MzPanicF(1, "MzBufferBlockCreateF failed");
  }
  MzBufferBlockInitF(block, framesCountP, channelsCountP);
  return block;
}

void MzBufferBlockInitF(MzBufferBlockZ *block, MzFramesT framesCountP,
                        MzChannelsT channelsCountP) {
  block->framesCountM = framesCountP;
  block->channelsCountM = channelsCountP;
  block->samplesCountM = framesCountP * channelsCountP;
  block->samplesM = malloc(block->samplesCountM * sizeof(MzSampleT));
  if (block->samplesM == NULL) {
    MzPanicF(1, "MzBufferBlockInitF failed");
  }
  for (MzIndexT i = 0; i < block->samplesCountM; i++) {
    block->samplesM[i] = 0;
  }
  block->isReadyM = true;
}

void MzBufferBlockFreeF(MzBufferBlockZ *block) { free(block->samplesM); }

void MzBufferBlockNotReadyF(MzBufferBlockZ *block) {
  for (MzIndexT i = 0; i < block->samplesCountM; i++) {
    block->samplesM[i] = 0;
  }
  block->isReadyM = false;
}
