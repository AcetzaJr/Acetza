#include "Muza/RT/Synth/Basic.h"

#include "Muza/Panic.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/Types.h"

#include <stdlib.h>
#include <string.h>

MzSynthZ *MzSynthBasicCreate() {
  MzSynthBasicZ *basicL = malloc(sizeof(MzSynthBasicZ));
  if (basicL == NULL) {
    MzPanicF(1, "MzSynthBasicCreate basicL is null");
  }
  for (MzIndexT i = 0; i < MzKeyCountD; i++) {
    basicL->stateM[i] = false;
  }
  return MzSynthCreateF(basicL, MzSynthBasicNoteOnF, MzSynthBasicNoteOffF,
                        MzSynthBasicPedalOnF, MzSynthBasicPedalOffF,
                        MzSynthBasicProcessBlockF, MzSynthBasicEndProcessBlockF,
                        MzSynthBasicFreeSynthF);
}
