#include "Muza/RT/Synth/Basic.h"

#include "Muza/Math.h"
#include "Muza/Panic.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/Scale.h"
#include "Muza/Types.h"

#include <glib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MzSynthZ *MzSynthBasicCreate() {
  MzSynthBasicZ *synthL = malloc(sizeof(MzSynthBasicZ));
  if (synthL == NULL) {
    MzPanicF(1, "MzSynthBasicCreate basicL is null");
  }
  synthL->attackIncrementM = MzFromDBF(-20);
  synthL->releaseDecrementM = MzFromDBF(-45);
  synthL->releaseEpsilonM = MzFromDBF(-20);
  for (MzNoteT noteIndexL = 0; noteIndexL < MzKeyCountD; noteIndexL++) {
    synthL->stateM[noteIndexL].typeM = MzIdleEK;
    synthL->stateM[noteIndexL].amplitudeM = 0;
    synthL->stateM[noteIndexL].frameM = 0;
    synthL->stateM[noteIndexL].frequencyM =
        MzScaleFrequencyF(&MzEqualTemperedG, noteIndexL - 62);
    g_mutex_init(&synthL->stateM[noteIndexL].mutexM);
    // printf("frequency %f\n", synthL->stateM[noteIndexL].frequencyM);
  }
  g_mutex_init(&synthL->processingMutexM);
  g_mutex_init(&synthL->stateMutexM);
  synthL->blockQueueM = g_async_queue_new();
  synthL->stateQueueM = g_async_queue_new();
  synthL->processingThreadM =
      g_thread_new("Prcessing", MzSynthBasicProcessingThread, synthL);
  synthL->poolM = g_thread_pool_new(MzSynthBasicPoolF, synthL, -1, FALSE, NULL);
  return MzSynthCreateF(synthL, MzSynthBasicNoteOnF, MzSynthBasicNoteOffF,
                        MzSynthBasicPedalOnF, MzSynthBasicPedalOffF,
                        MzSynthBasicProcessBlockF, MzSynthBasicEndProcessBlockF,
                        MzSynthBasicFreeSynthF);
}
