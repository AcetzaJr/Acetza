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
} MzBufferBlockZ;

extern MzBufferBlockZ MzBlockG;

void MzBlockCopyF(MzBufferBlockZ *blockP, MzBufferBlockZ *fromP);

void MzBlockWaveF(MzBufferBlockZ *blockP, MzWaveZ *waveP);

MzFrequencyT MzBlockFrequencyF(MzBufferBlockZ *blockP);

void MzBlockSetFrequencyF(MzBufferBlockZ *blockP, MzFrequencyT frequencyP);

void MzBlockSetDurationF(MzBufferBlockZ *blockP, MzDurationT durationP);
