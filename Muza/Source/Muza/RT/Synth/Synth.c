#include "Muza/RT/Synth/Synth.h"
#include "Muza/Panic.h"

#include <stdlib.h>

MzSynthZ *MzSynthCreateF(void *synthP, MzNoteOnT noteOnP, MzNoteOffT noteOffP,
                         MzPedalOnT pedalOnP, MzPedalOffT pedalOffP,
                         MzProcessBlockT processBlockP,
                         MzEndProcessBlockT endProcessBlockP,
                         MzFreeSynthT freeSynthP) {

  MzSynthZ *synthL = malloc(sizeof(MzSynthZ));
  if (synthL == NULL) {
    MzPanicF(1, "MzSynthCreate synthL is null");
  }
  synthL->synthM = synthP;
  synthL->noteOnM = noteOnP;
  synthL->noteOffM = noteOffP;
  synthL->pedalOnM = pedalOnP;
  synthL->pedalOffM = pedalOffP;
  synthL->processBlockM = processBlockP;
  synthL->endProcessBlockM = endProcessBlockP;
  synthL->freeSynthM = freeSynthP;
  return synthL;
}

void MzSynthFreeF(MzSynthZ *synthP) {
  synthP->freeSynthM(NULL, synthP->synthM);
  free(synthP);
}
