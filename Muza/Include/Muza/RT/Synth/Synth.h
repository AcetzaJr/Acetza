#pragma once

#include "Muza/RT/Synth/Interface.h"

typedef struct {
  void *synthM;
  MzNoteOnT noteOnM;
  MzNoteOffT noteOffM;
  MzProcessBlockT processBlockM;
} MzSynthZ;
