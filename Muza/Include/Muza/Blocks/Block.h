#pragma once

#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef enum { MzBlockK, MzBasicK, MzEnveloperK, MzHarmonizerK } MzBlockTypeE;

typedef struct {
  MzBlockTypeE type;
  void *block;
} MzBlockZ;

extern MzBlockZ MzBlockR;

void MzBlockCopy(MzBlockZ *block, MzBlockZ *from);

void MzBlockWave(MzBlockZ *block, MzWaveZ *wave);

MzFrequencyT MzBlockFrequency(MzBlockZ *block);

void MzBlockSetFrequency(MzBlockZ *block, MzFrequencyT frequency);

void MzBlockSetDuration(MzBlockZ *block, MzDurationT duration);
