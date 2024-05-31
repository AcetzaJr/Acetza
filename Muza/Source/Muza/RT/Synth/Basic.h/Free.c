#include "Muza/RT/Synth/Basic.h"
#include "glibconfig.h"

#include <stdlib.h>

void MzSynthBasicFreeSynthF(void * /*dataP*/, void *synthP) {
  MzSynthBasicZ *synthL = synthP;
  g_thread_join(synthL->processingThreadM);
  g_thread_pool_free(synthL->poolM, FALSE, TRUE);
  g_mutex_clear(&synthL->processingMutexM);
  g_mutex_clear(&synthL->stateMutexM);
  for (MzNoteT noteIndexL = 0; noteIndexL < MzKeyCountD; noteIndexL++) {
    g_mutex_clear(&synthL->stateM[noteIndexL].mutexM);
    // printf("frequency %f\n", synthL->stateM[noteIndexL].frequencyM);
  }
  g_async_queue_unref(synthL->blockQueueM);
  g_async_queue_unref(synthL->stateQueueM);
  free(synthL);
}
