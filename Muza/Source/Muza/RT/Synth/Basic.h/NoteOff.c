#include "Muza/RT/Synth/Basic.h"

void MzSynthBasicNoteOffF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                          u8T keyP, u8T /*velocityP*/) {
  MzSynthBasicZ *synthL = synthP;
  MzSynthBasicStateZ *stateL = &synthL->stateM[keyP];
  g_mutex_lock(&stateL->mutexM);
  stateL->typeM = MzReleasingEK;
  g_mutex_unlock(&stateL->mutexM);
}
