#include "Muza/Scale.h"

#include "Muza/Math.h"
#include "Muza/Types.h"

#include <math.h>

MzFrequencyT MzAcetzaRations[] = {(MzFrequencyT)1 / 1,
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

MzScaleZ MzAcetzaR;

void MzAcetzaInit(MzFrequencyT base) {
  MzAcetzaR.base = base;
  MzAcetzaR.count = 12;
  MzAcetzaR.rations = MzAcetzaRations;
  MzAcetzaR.rations[6] = MzEqualTempered(6, 1);
}

MzFrequencyT MzEqualTempered(MzNoteT note, MzFrequencyT base) {
  return base * pow(2, note / 12);
}

MzFrequencyT MzScalePower(MzNoteT note, MzCountT count) {
  return note < 0 ? (note + 1) / count - 1 : note / count;
}

MzFrequencyT MzScaleFrequency(MzScaleZ *scale, MzNoteT note) {
  return scale->base * AzPosModU64(note, scale->count) *
         pow(2, MzScalePower(note, scale->count));
}
