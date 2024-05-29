#include "Muza/RT/WaveBuffer.h"

#include "Muza/Panic.h"
#include "Muza/RT/BufferBlock.h"
#include "Muza/Types.h"

#include <stdlib.h>

void MzWaveBufferInitF(MzWaveBufferZ *bufferP, MzCountT blocksCountP,
                       MzFramesT framesCountP, MzChannelsT channelsCountP) {
  bufferP->blocksCountM = blocksCountP;
  bufferP->activeBlockM = MzBufferBlockCreateF(framesCountP, channelsCountP);
  bufferP->blocksM = malloc(sizeof(MzBufferBlockZ *) * blocksCountP);
  if (bufferP->blocksM == NULL) {
    MzPanicF(1, "MzWaveBufferInitF failed");
  }
  for (MzIndexT i = 0; i < blocksCountP; i++) {
    bufferP->blocksM[i] = MzBufferBlockCreateF(framesCountP, channelsCountP);
  }
}

void MzWaveBufferFreeF(MzWaveBufferZ *buffer) {
  MzBufferBlockFreeF(buffer->activeBlockM);
  free(buffer->activeBlockM);
  for (MzIndexT i = 0; i < buffer->blocksCountM; i++) {
    MzBufferBlockFreeF(buffer->blocksM[i]);
    free(buffer->blocksM[i]);
  }
  free(buffer->blocksM);
}
