#pragma once

#include "Muza/Types.h"

typedef struct {
  MzFrequencyT *rations;
  MzFrequencyT base;
  MzCountT count;
} MzScaleZ;

extern MzScaleZ MzAcetzaR;

void MzAcetzaInit(MzFrequencyT base);

MzFrequencyT MzScaleFrequency(MzScaleZ *scale, MzNoteT note);

MzFrequencyT MzEqualTempered(MzNoteT note, MzFrequencyT base);
