#pragma once

#include "Muza/Blocks/Block.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzBufferBlockZ *blockM;
  MzDepthT depthM;
  MzNumbererT numbererM;
} MzHarmonizerZ;

extern MzHarmonizerZ MzHarmonizerG;

void MzHarmonizerCopyF(MzHarmonizerZ *harmonizerP, MzHarmonizerZ *fromP);

void MzHarmonizerWaveF(MzHarmonizerZ *harmonizerP, MzWaveZ *waveP);

MzFrequencyT MzHarmonizerFrequencyF(MzHarmonizerZ *harmonizerP);

void MzHarmonizerSetFrequencyF(MzHarmonizerZ *harmonizerP,
                               MzFrequencyT frequencyP);

void MzHarmonizerSetDurationF(MzHarmonizerZ *harmonizerP,
                              MzDurationT durationP);
