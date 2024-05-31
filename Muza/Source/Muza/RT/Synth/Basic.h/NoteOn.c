#include "Muza/Common.h"
#include "Muza/Math.h"
#include "Muza/RT/Synth/Basic.h"

#include "Muza/Types.h"

MzDBT MzDBRangeG = 30;
MzDBT MzDBLimitG = 1;

void MzSynthBasicNoteOnF(void * /*dataP*/, void *synthP, u8T /*channelP*/,
                         u8T keyP, u8T velocityP) {
  MzSynthBasicZ *synthL = synthP;
  MzSynthBasicStateZ *stateL = &synthL->stateM[keyP];
  g_mutex_lock(&stateL->mutexM);
  stateL->typeM = MzAttackingEK;
  MzDBT targetL =
      (MzDBT)velocityP / 127.0 * MzDBRangeG - MzDBRangeG - MzDBLimitG;
  stateL->targetM = MzFromDBF(targetL);
  // printf("%f\n", synthL->stateM[keyP].targetM);
  g_mutex_unlock(&stateL->mutexM);
}
