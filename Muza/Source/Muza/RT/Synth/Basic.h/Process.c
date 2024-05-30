#include "Muza/RT/Synth/Basic.h"

#include "Muza/RT/Session.h"

#include <glib.h>
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
    MzBufferBlockZ *blockL =
        g_async_queue_timeout_pop(synthL->blockQueueM, 100'000);
    if (blockL == NULL) {
      continue;
    }
    for (MzIndexT i = 0; i < MzKeyCountD; i++) {
      bool stateL;
      g_mutex_lock(&synthL->stateMutexM);
      stateL = synthL->stateM[i];
      g_mutex_unlock(&synthL->stateMutexM);
      if (stateL) {
        printf("push\n");
        g_thread_pool_push(synthL->poolM, (gpointer)i, NULL);
      }
    }
    g_mutex_unlock(&synthL->processingMutexM);
  }
  return NULL;
}

void MzSynthBasicPoolF(gpointer dataP, gpointer userDataP) {
  unsigned long dataL = (unsigned long)dataP;
  printf("dataL %lu\n", dataL);
  unsigned long userDataL = (unsigned long)userDataP;
  printf("userDataL %lu\n", userDataL);
}
