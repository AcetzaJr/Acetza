#include "Muza/RT/Synth/Basic.h"

#include <stdlib.h>

void MzSynthBasicFreeSynthF(void * /*dataP*/, void *synthP) {
  MzSynthBasicZ *synthL = synthP;
  g_thread_join(synthL->processingThreadM);
  g_mutex_clear(&synthL->processingMutexM);
  g_async_queue_unref(synthL->blockQueueM);
  free(synthL);
}
