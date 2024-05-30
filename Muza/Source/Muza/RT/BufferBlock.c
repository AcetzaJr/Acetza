#include "Muza/RT/BufferBlock.h"

#include "Muza/Panic.h"
#include "Muza/Types.h"
#include "glib.h"

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

void MzBufferBlockInitF(MzBufferBlockZ *blockP, MzFramesT framesCountP,
                        MzChannelsT channelsCountP) {
  blockP->framesCountM = framesCountP;
  blockP->channelsCountM = channelsCountP;
  blockP->samplesCountM = framesCountP * channelsCountP;
  blockP->samplesM = malloc(blockP->samplesCountM * sizeof(MzSampleT));
  if (blockP->samplesM == NULL) {
    MzPanicF(1, "MzBufferBlockInitF failed");
  }
  for (MzIndexT i = 0; i < blockP->samplesCountM; i++) {
    blockP->samplesM[i] = 0;
  }
  g_mutex_init(&blockP->samplesMutexM);
  blockP->isReadyM = true;
}

void MzBufferBlockFreeF(MzBufferBlockZ *blockP) {
  g_mutex_clear(&blockP->samplesMutexM);
  free(blockP->samplesM);
}

void MzBufferBlockNotReadyF(MzBufferBlockZ *blockP) {
  for (MzIndexT i = 0; i < blockP->samplesCountM; i++) {
    blockP->samplesM[i] = 0;
  }
  blockP->isReadyM = false;
}

MzSampleT *MzBufferBlockLock(MzBufferBlockZ *blockP, MzFrameT frameP,
                             MzChannelT channelP) {
  g_mutex_lock(&blockP->samplesMutexM);
  return &blockP->samplesM[frameP * blockP->channelsCountM + channelP];
}

void MzBufferBlockUnLock(MzBufferBlockZ *blockP) {
  g_mutex_unlock(&blockP->samplesMutexM);
}
