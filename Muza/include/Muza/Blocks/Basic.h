#pragma once

#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzPrimitiveF primitive;
  MzFrequencyT frequency;
  MzDurationT duration;
  MzChannelsT channels;
  MzFrameRateT frameRate;
} MzBasicZ;

void MzBasicWave(MzBasicZ *basic, MzWaveZ *wave);

MzFrequencyT MzBasicFrequency(MzBasicZ *basic);

void MzBasicSetFrequency(MzBasicZ *basic, MzFrequencyT frequency);

void MzBasicSetDuration(MzBasicZ *basic, MzDurationT duration);
