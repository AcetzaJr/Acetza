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
    g_mutex_unlock(&synthL->processingMutexM);
  }
  return NULL;
}
