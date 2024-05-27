#pragma once

#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzPrimitiveFT primitiveM;
  MzFrequencyT frequencyM;
  MzDurationT durationM;
  MzAmplitudeT amplitudeM;
  MzChannelsT channelsM;
  MzFrameRateT frameRateM;
} MzBasicZ;

extern MzBasicZ MzBasicG;

void MzBasicCopyF(MzBasicZ *basicP, MzBasicZ *fromP);

void MzBasicWaveF(MzBasicZ *basicP, MzWaveZ *waveP);

MzFrequencyT MzBasicFrequencyF(MzBasicZ *basicP);

void MzBasicSetFrequencyF(MzBasicZ *basicP, MzFrequencyT frequencyP);

void MzBasicSetDurationF(MzBasicZ *basicP, MzDurationT durationP);
