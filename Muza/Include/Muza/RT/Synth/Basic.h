#pragma once

#include "Muza/Constants.h"
#include "Muza/RT/BufferBlock.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/Types.h"

#include <glib.h>

typedef struct {
  MzTimeT timeM;
  MzFrequencyT frequencyM;
  MzAmplitudeT amplitudeM;
  bool pressedM;
} MzSynthBasicStateZ;

typedef struct {
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
