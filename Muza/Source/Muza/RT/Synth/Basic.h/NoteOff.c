#include "Muza/RT/Synth/Basic.h"

void MzSynthBasicNoteOffF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                          u8T keyP, u8T /*velocityP*/) {
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->stateMutexM);
  synthL->stateM[keyP].typeM = MzReleasingEK;
  g_mutex_unlock(&synthL->stateMutexM);
}
