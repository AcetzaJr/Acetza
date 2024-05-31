#include "Muza/Scale.h"

#include "Muza/Common.h"
#include "Muza/Math.h"
#include "Muza/Types.h"

#include <math.h>

MzFrequencyT MzAcetzaRationsG[12] = {(MzFrequencyT)1 / 1,
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

MzFrequencyT MzEqualTemperedRationsG[12];

MzScaleZ MzAcetzaG;
MzScaleZ MzEqualTemperedG;

void MzEqualTemperedInitF(MzFrequencyT baseP) {
  MzEqualTemperedG.baseM = baseP;
  MzEqualTemperedG.countM = 12;
  MzEqualTemperedG.rationsM = MzEqualTemperedRationsG;
  MzEqualTemperedG.rationsM[0] = MzEqualTemperedF(0, 1);
  MzEqualTemperedG.rationsM[1] = MzEqualTemperedF(1, 1);
  MzEqualTemperedG.rationsM[2] = MzEqualTemperedF(2, 1);
  MzEqualTemperedG.rationsM[3] = MzEqualTemperedF(3, 1);
  MzEqualTemperedG.rationsM[4] = MzEqualTemperedF(4, 1);
  MzEqualTemperedG.rationsM[5] = MzEqualTemperedF(5, 1);
  MzEqualTemperedG.rationsM[6] = MzEqualTemperedF(6, 1);
  MzEqualTemperedG.rationsM[7] = MzEqualTemperedF(7, 1);
  MzEqualTemperedG.rationsM[8] = MzEqualTemperedF(8, 1);
  MzEqualTemperedG.rationsM[9] = MzEqualTemperedF(9, 1);
  MzEqualTemperedG.rationsM[10] = MzEqualTemperedF(10, 1);
  MzEqualTemperedG.rationsM[11] = MzEqualTemperedF(11, 1);
}

void MzAcetzaInitF(MzFrequencyT baseP) {
  MzAcetzaG.baseM = baseP;
  MzAcetzaG.countM = 12;
  MzAcetzaG.rationsM = MzAcetzaRationsG;
  MzAcetzaG.rationsM[6] = MzEqualTemperedF(6, 1);
}

MzFrequencyT MzEqualTemperedF(MzNoteT noteP, MzFrequencyT baseP) {
  return baseP * pow(2, (double)noteP / 12);
}

i64T MzScalePowerF(MzNoteT noteP, i64T countP) {
  return noteP < 0 ? (noteP + 1) / countP - 1 : noteP / countP;
}

MzFrequencyT MzScaleFrequencyF(MzScaleZ *scaleP, MzNoteT noteP) {
  MzIndexT indexL = MzPosModi64F(noteP, (i64T)scaleP->countM);
  // printf("index %lu\n", indexL);
  return scaleP->baseM * scaleP->rationsM[indexL] *
         pow(2, (MzFrequencyT)MzScalePowerF(noteP, (i64T)scaleP->countM));
}
