#pragma once

#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef enum {
  MzBlockEK,
  MzBasicEK,
  MzEnveloperEK,
  MzHarmonizerEK
} MzBlockTypeE;

typedef struct {
  MzBlockTypeE typeM;
  void *blockM;
} MzBlockZ;

extern MzBlockZ MzBlockG;

void MzBlockCopyF(MzBlockZ *blockP, MzBlockZ *fromP);

void MzBlockWaveF(MzBlockZ *blockP, MzWaveZ *waveP);

MzFrequencyT MzBlockFrequencyF(MzBlockZ *blockP);

void MzBlockSetFrequencyF(MzBlockZ *blockP, MzFrequencyT frequencyP);

void MzBlockSetDurationF(MzBlockZ *blockP, MzDurationT durationP);
