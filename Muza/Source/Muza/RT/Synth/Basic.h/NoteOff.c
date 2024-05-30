#include "Muza/RT/Synth/Basic.h"

void MzSynthBasicNoteOffF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                          u8T keyP, u8T /*velocityP*/) {
  MzSynthBasicZ *synthL = synthP;
  synthL->stateM[keyP] = false;
}
