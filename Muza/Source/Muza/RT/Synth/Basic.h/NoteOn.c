#include "Muza/Math.h"
#include "Muza/RT/Synth/Basic.h"

#include "Muza/Types.h"

void MzSynthBasicNoteOnF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                         u8T keyP, u8T velocityP) {
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->stateMutexM);
  synthL->stateM[keyP].pressedM = true;
  synthL->stateM[keyP].timeM = 0;
  MzDBT amplitudeL = (MzDBT)velocityP / 127.0 * 20.0 - 20.0 - 6.0;
  synthL->stateM[keyP].amplitudeM = MzFromDBF(amplitudeL);
  g_mutex_unlock(&synthL->stateMutexM);
}
