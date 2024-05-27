#pragma once

#include "Muza/Blocks/Enveloper.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzTimeT time;
  MzAmplitudeT amplitude;
} MzUntilZ;

typedef struct {
  bool disrupted;
  MzTimeT time;
  MzAmplitudeT amplitude;
} MzTransformResultZ;

MzUntilZ MzUntilRelease(MzEnveloperZ *enveloper, MzWaveZ *wave,
                        MzDurationT duration);

MzTransformResultZ MzTransform(MzWaveZ *wave, MzTransformerF transformer,
                               MzTimeT startTime, MzAmplitudeT startAmplitude,
                               MzTimeT endTime, MzAmplitudeT endAmplitude,
                               MzTimeT limit);
