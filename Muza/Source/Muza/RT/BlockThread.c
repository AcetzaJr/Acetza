#include "Muza/RT/BlockThread.h"

#include "Muza/RT/Session.h"

#include <glib.h>
#include <stdio.h>
#include <time.h>

int MzBlockHandlerF(void * /*dataP*/) {
  while (MzSessionG.processingM) {
    MzBufferBlockZ *blockL =
        g_async_queue_timeout_pop(MzSessionG.blockQueueM, 100'000);
    if (blockL == NULL) {
      continue;
    }
    blockL->isReadyM = true;
    // printf("block processed\n");
  }
  return 0;
}
