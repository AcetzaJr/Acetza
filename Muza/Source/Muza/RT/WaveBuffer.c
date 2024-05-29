#include "Muza/RT/WaveBuffer.h"

#include "Muza/Panic.h"
#include "Muza/RT/BufferBlock.h"
#include "Muza/RT/Session.h"
#include "Muza/Types.h"

#include <glib.h>

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
  bufferP->sampleIndexM = 0;
}

void MzWaveBufferFreeF(MzWaveBufferZ *bufferP) {
  MzBufferBlockFreeF(bufferP->activeBlockM);
  free(bufferP->activeBlockM);
  for (MzIndexT i = 0; i < bufferP->blocksCountM; i++) {
    MzBufferBlockFreeF(bufferP->blocksM[i]);
    free(bufferP->blocksM[i]);
  }
  free(bufferP->blocksM);
}

double MzWaveBufferNextSampleF(MzWaveBufferZ *bufferP) {
  if (bufferP->sampleIndexM >= bufferP->activeBlockM->samplesCountM) {
    if (!MzWaveBufferTrySwapF(bufferP)) {
      return 0;
    }
  }
  return bufferP->activeBlockM->samplesM[bufferP->sampleIndexM++];
}

bool MzWaveBufferTrySwapF(MzWaveBufferZ *bufferP) {
  MzBufferBlockZ *lastL = bufferP->blocksM[bufferP->blocksCountM - 1];
  if (!lastL->isReadyM) {
    return false;
  }
  bufferP->sampleIndexM = 0;
  MzBufferBlockZ *swapL = bufferP->activeBlockM;
  MzBufferBlockNotReadyF(swapL);
  g_async_queue_push(MzSessionG.blockQueueM, swapL);
  bufferP->activeBlockM = lastL;
  for (MzIndexT i = bufferP->blocksCountM - 2; i >= 0; i--) {
    bufferP->blocksM[i + 1] = bufferP->blocksM[i];
  }
  bufferP->blocksM[0] = swapL;
  return true;
}
