#pragma once

#include "Muza/RT/Synth/Interface.h"

typedef struct {
  void *synthM;
  MzNoteOnT noteOnM;
  MzNoteOffT noteOffM;
  MzPedalOnT pedalOnM;
  MzPedalOffT pedalOffM;
  MzProcessBlockT processBlockM;
  MzEndProcessBlockT endProcessBlockM;
  MzFreeSynthT freeSynthM;
} MzSynthZ;

MzSynthZ *MzSynthCreateF(void *synthP, MzNoteOnT noteOnP, MzNoteOffT noteOffP,
                         MzPedalOnT pedalOnP, MzPedalOffT pedalOffP,
                         MzProcessBlockT processBlockP,
                         MzEndProcessBlockT endProcessBlockP,
                         MzFreeSynthT freeSynthP);

void MzSynthFreeF(MzSynthZ *synthP);
