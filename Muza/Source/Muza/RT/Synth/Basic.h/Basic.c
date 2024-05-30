#include "Muza/RT/Synth/Basic.h"

#include "Muza/Panic.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/Types.h"
#include "glib.h"

#include <stdlib.h>
#include <string.h>

MzSynthZ *MzSynthBasicCreate() {
  MzSynthBasicZ *synthL = malloc(sizeof(MzSynthBasicZ));
  if (synthL == NULL) {
    MzPanicF(1, "MzSynthBasicCreate basicL is null");
  }
  for (MzIndexT i = 0; i < MzKeyCountD; i++) {
    synthL->stateM[i] = false;
  }
  g_mutex_init(&synthL->processingMutexM);
  synthL->blockQueueM = g_async_queue_new();
  synthL->processingThreadM =
      g_thread_new("Prcessing", MzSynthBasicProcessingThread, synthL);
  return MzSynthCreateF(synthL, MzSynthBasicNoteOnF, MzSynthBasicNoteOffF,
                        MzSynthBasicPedalOnF, MzSynthBasicPedalOffF,
                        MzSynthBasicProcessBlockF, MzSynthBasicEndProcessBlockF,
                        MzSynthBasicFreeSynthF);
}
