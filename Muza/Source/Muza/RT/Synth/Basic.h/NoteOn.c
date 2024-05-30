#include "Muza/RT/Synth/Basic.h"

#include <stdio.h>

void MzSynthBasicNoteOnF(void * /*dataP*/, void *synthP, u8T channelP, u8T keyP,
                         u8T velocityP) {
  printf("channelP %d, keyP %d, velocityP %d\n", channelP, keyP, velocityP);
  MzSynthBasicZ *synthL = synthP;
  synthL->stateM[keyP] = true;
}
