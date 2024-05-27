#include "Muza/Scale.h"

#include "Muza/Math.h"
#include "Muza/Types.h"

#include <math.h>

MzFrequencyT MzAcetzaRationsG[] = {(MzFrequencyT)1 / 1,
                                   (MzFrequencyT)256 / 243,
                                   (MzFrequencyT)9 / 8,
                                   (MzFrequencyT)32 / 27,
                                   (MzFrequencyT)81 / 64,
                                   (MzFrequencyT)4 / 3,
                                   0,
                                   (MzFrequencyT)3 / 2,
                                   (MzFrequencyT)128 / 81,
                                   (MzFrequencyT)27 / 16,
                                   (MzFrequencyT)16 / 9,
                                   (MzFrequencyT)243 / 128};

MzScaleZ MzAcetzaG;

void MzAcetzaInitF(MzFrequencyT baseP) {
  MzAcetzaG.baseM = baseP;
  MzAcetzaG.countM = 12;
  MzAcetzaG.rationsM = MzAcetzaRationsG;
  MzAcetzaG.rationsM[6] = MzEqualTemperedF(6, 1);
}

MzFrequencyT MzEqualTemperedF(MzNoteT noteP, MzFrequencyT baseP) {
  return baseP * pow(2, noteP / 12);
}

MzFrequencyT MzScalePowerF(MzNoteT noteP, MzCountT countP) {
  return noteP < 0 ? (noteP + 1) / countP - 1 : noteP / countP;
}

MzFrequencyT MzScaleFrequencyF(MzScaleZ *scaleP, MzNoteT noteP) {
  return scaleP->baseM * MzPosModi64F(noteP, scaleP->countM) *
         pow(2, MzScalePowerF(noteP, scaleP->countM));
}
