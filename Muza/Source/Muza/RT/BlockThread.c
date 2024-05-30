#include "Muza/RT/BlockThread.h"

#include "Muza/RT/Session.h"

#include <stdio.h>
#include <time.h>

gpointer MzBlockHandlerF(gpointer /*dataP*/) {
  while (MzSessionG.processingM) {
    MzBufferBlockZ *blockL =
        g_async_queue_timeout_pop(MzSessionG.blockQueueM, 100'000);
    if (blockL == NULL) {
      continue;
    }
    // rintf("processing block\n");
    MzSessionG.synthM->processBlockM(NULL, MzSessionG.synthM->synthM, blockL);
    MzSessionG.synthM->endProcessBlockM(NULL, MzSessionG.synthM->synthM,
                                        blockL);
    blockL->isReadyM = true;
    // printf("block processed\n");
  }
  return NULL;
}
