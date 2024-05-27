#pragma once

#include "Muza/Blocks/Block.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzBlockZ *block;
  MzDepthT depth;
  MzNumbererF numberer;
} MzHarmonizerZ;

extern MzHarmonizerZ MzHarmonizerR;

void MzHarmonizerCopy(MzHarmonizerZ *harmonizer, MzHarmonizerZ *from);

void MzHarmonizerWave(MzHarmonizerZ *harmonizer, MzWaveZ *wave);

MzFrequencyT MzHarmonizerFrequency(MzHarmonizerZ *harmonizer);

void MzHarmonizerSetFrequency(MzHarmonizerZ *harmonizer,
                              MzFrequencyT frequency);

void MzHarmonizerSetDuration(MzHarmonizerZ *harmonizer, MzDurationT duration);
