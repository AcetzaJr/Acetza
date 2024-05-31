#include "Muza/RT/Synth/Basic.h"

#include "Muza/FrameRate.h"
#include "Muza/Functions/Primitives.h"
#include "Muza/RT/BufferBlock.h"
#include "Muza/RT/Session.h"
#include "Muza/Types.h"

#include <glib.h>

#include <math.h>
#include <stdio.h>

void MzSynthBasicProcessBlockF(void * /*dataP*/, void *synthP,
                               MzBufferBlockZ *blockP) {
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->processingMutexM);
  g_async_queue_push(synthL->blockQueueM, blockP);
}

void MzSynthBasicEndProcessBlockF(void * /*dataP*/, void *synthP,
                                  MzBufferBlockZ * /*blockP*/) {
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->processingMutexM);
  g_mutex_unlock(&synthL->processingMutexM);
}

gpointer MzSynthBasicProcessingThread(gpointer synthP) {
  MzSynthBasicZ *synthL = synthP;
  while (MzSessionG.processingM) {
    synthL->blockM = g_async_queue_timeout_pop(synthL->blockQueueM, 100'000);
    if (synthL->blockM == NULL) {
      continue;
    }
    MzCountT countL = 0;
    for (MzIndexT indexL = 0; indexL < MzKeyCountD; indexL++) {
      bool pressedL;
      g_mutex_lock(&synthL->stateMutexM);
      pressedL = synthL->stateM[indexL].pressedM;
      g_mutex_unlock(&synthL->stateMutexM);
      if (pressedL) {
        countL++;
        g_thread_pool_push(synthL->poolM, &synthL->stateM[indexL], NULL);
      }
    }
    for (MzIndexT indexL = 0; indexL < countL; indexL++) {
      g_async_queue_pop(synthL->stateQueueM);
    }
    g_mutex_unlock(&synthL->processingMutexM);
  }
  return NULL;
}

void MzSynthBasicPoolF(gpointer dataP, gpointer userDataP) {
  MzSynthBasicStateZ *stateL = dataP;
  // printf("frequencyL %f\n", stateL->frequencyM);
  MzSynthBasicZ *synthL = userDataP;
  for (MzIndexT frameL = 0; frameL < synthL->blockM->framesCountM; frameL++) {
    MzTimeT timeL =
        stateL->timeM + MzFrameToTimeF(frameL, MzSessionG.frameRateM);
    MzPartT partL = fmod(timeL * stateL->frequencyM, 1.0);
    MzSampleT sampleL = MzPrimitivesSinF(partL) * stateL->amplitudeM;
    for (MzIndexT channelL = 0; channelL < synthL->blockM->channelsCountM;
         ++channelL) {
      MzSampleT *ptrL = MzBufferBlockLock(synthL->blockM, frameL, channelL);
      *ptrL += sampleL;
      MzBufferBlockUnLock(synthL->blockM);
    }
  }
  stateL->timeM +=
      MzFrameToTimeF(synthL->blockM->framesCountM, MzSessionG.frameRateM);
  g_async_queue_push(synthL->stateQueueM, stateL);
}
