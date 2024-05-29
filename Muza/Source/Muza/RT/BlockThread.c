#include "Muza/RT/BlockThread.h"

#include "Muza/RT/Session.h"

#include <glib.h>
#include <stdio.h>
#include <time.h>

int MzBlockHandlerF(void * /*dataP*/) {
  while (MzSessionG.runningM) {
    MzBufferBlockZ *blockL;
    while ((blockL = g_async_queue_timeout_pop(MzSessionG.blockQueueM,
                                               1'000'000)) == NULL) {
    };
    blockL->isReadyM = true;
    printf("block processed\n");
  }
  return 0;
}
