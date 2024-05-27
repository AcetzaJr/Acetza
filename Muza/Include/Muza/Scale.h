#pragma once

#include "Muza/Types.h"

typedef struct {
  MzFrequencyT *rationsM;
  MzFrequencyT baseM;
  MzCountT countM;
} MzScaleZ;

extern MzScaleZ MzAcetzaG;

void MzAcetzaInitF(MzFrequencyT baseP);

MzFrequencyT MzScaleFrequencyF(MzScaleZ *scaleP, MzNoteT noteP);

MzFrequencyT MzEqualTemperedF(MzNoteT noteP, MzFrequencyT baseP);
