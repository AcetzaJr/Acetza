#pragma once

#include "Muza/Constants.h"
#include "Muza/RT/Synth/Synth.h"

#include <glib.h>

typedef struct {
  GThreadPool *poolM;
  GThread *processingThreadM;
  GAsyncQueue *blockQueueM;
  GMutex processingMutexM;
  GMutex stateMutexM;
  bool stateM[MzKeyCountD];
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
