#pragma once

#include "Muza/Constants.h"
#include "Muza/RT/BufferBlock.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/Types.h"

#include <glib.h>

typedef enum {
  MzIdleEK,
  MzAttackingEK,
  MzHoldingEK,
  MzReleasingEK,
  MzEndingEK
} MzStateE;

typedef struct {
  MzIndexT frameM;
  MzFrequencyT frequencyM;
  MzAmplitudeT amplitudeM;
  MzAmplitudeT targetM;
  MzStateE typeM;
  GMutex mutexM;
} MzSynthBasicStateZ;

typedef struct {
  MzAmplitudeT attackIncrementM;
  MzAmplitudeT releaseDecrementM;
  MzAmplitudeT releaseEpsilonM;
  MzBufferBlockZ *blockM;
  GThreadPool *poolM;
  GThread *processingThreadM;
  GAsyncQueue *blockQueueM;
  GAsyncQueue *stateQueueM;
  GMutex processingMutexM;
  GMutex stateMutexM;
  MzSynthBasicStateZ stateM[MzKeyCountD];
} MzSynthBasicZ;

MzSynthZ *MzSynthBasicCreate();

void MzSynthBasicNoteOnF(void *dataP, void *synthP, u8T channelP, u8T keyP,
                         u8T velocityP);

void MzSynthBasicNoteOffF(void *dataP, void *synthP, u8T channelP, u8T keyP,
                          u8T velocityP);

void MzSynthBasicPedalOnF(void *dataP, void *synthP, u8T channelP);

void MzSynthBasicPedalOffF(void *dataP, void *synthP, u8T channelP);

void MzSynthBasicProcessBlockF(void *dataP, void *synthP,
                               MzBufferBlockZ *blockP);

void MzSynthBasicEndProcessBlockF(void *dataP, void *synthP,
                                  MzBufferBlockZ *blockP);

void MzSynthBasicFreeSynthF(void *dataP, void *synthP);

gpointer MzSynthBasicProcessingThread(gpointer);

void MzSynthBasicPoolF(gpointer dataP, gpointer userDataP);
