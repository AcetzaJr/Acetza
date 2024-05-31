#pragma once

#include "Muza/Types.h"

typedef struct {
  MzFrequencyT *rationsM;
  MzFrequencyT baseM;
  MzCountT countM;
} MzScaleZ;

extern MzScaleZ MzAcetzaG;
extern MzScaleZ MzEqualTemperedG;

void MzAcetzaInitF(MzFrequencyT baseP);

void MzEqualTemperedInitF(MzFrequencyT baseP);

MzFrequencyT MzScaleFrequencyF(MzScaleZ *scaleP, MzNoteT noteP);

MzFrequencyT MzEqualTemperedF(MzNoteT noteP, MzFrequencyT baseP);
