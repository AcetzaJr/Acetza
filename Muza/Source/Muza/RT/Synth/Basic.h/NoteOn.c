#include "Muza/Math.h"
#include "Muza/RT/Synth/Basic.h"

#include "Muza/Types.h"

void MzSynthBasicNoteOnF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                         u8T keyP, u8T velocityP) {
  MzSynthBasicZ *synthL = synthP;
  g_mutex_lock(&synthL->stateMutexM);
  synthL->stateM[keyP].typeM = MzAttackingEK;
  MzDBT targetL = (MzDBT)velocityP / 127.0 * 20.0 - 20.0 - 6.0;
  synthL->stateM[keyP].targetM = MzFromDBF(targetL);
  // printf("%f\n", synthL->stateM[keyP].targetM);
  g_mutex_unlock(&synthL->stateMutexM);
}
