#include "Muza/RT/Synth/Basic.h"
#include "glib.h"

#include <stdio.h>

void MzSynthBasicNoteOnF(void * /*dataP*/, void *synthP, u8T channelP, u8T keyP,
                         u8T velocityP) {
  printf("channelP %d, keyP %d, velocityP %d\n", channelP, keyP, velocityP);
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->stateMutexM);
  synthL->stateM[keyP].pressedM = true;
  synthL->stateM[keyP].timeM = 0;
  g_mutex_unlock(&synthL->stateMutexM);
}
