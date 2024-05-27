#pragma once

#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzPrimitiveF primitive;
  MzFrequencyT frequency;
  MzDurationT duration;
  MzAmplitudeT amplitude;
  MzChannelsT channels;
  MzFrameRateT frameRate;
} MzBasicZ;

extern MzBasicZ MzBasicR;

void MzBasicCopy(MzBasicZ *basic, MzBasicZ *from);

void MzBasicWave(MzBasicZ *basic, MzWaveZ *wave);

MzFrequencyT MzBasicFrequency(MzBasicZ *basic);

void MzBasicSetFrequency(MzBasicZ *basic, MzFrequencyT frequency);

void MzBasicSetDuration(MzBasicZ *basic, MzDurationT duration);
