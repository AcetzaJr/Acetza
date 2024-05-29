#pragma once

#include "Muza/Blocks/Enveloper.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzTimeT timeM;
  MzAmplitudeT amplitudeM;
} MzUntilZ;

typedef struct {
  bool disruptedM;
  MzTimeT timeM;
  MzAmplitudeT amplitudeM;
} MzTransformResultZ;

MzUntilZ MzUntilReleaseF(MzEnveloperZ *enveloperP, MzWaveZ *waveP,
                         MzDurationT durationP);

MzTransformResultZ MzTransformF(MzWaveZ *waveP, MzTransformerT transformerP,
                                MzTimeT startTimeP,
                                MzAmplitudeT startAmplitudeP, MzTimeT endTimeP,
                                MzAmplitudeT endAmplitudeP, MzTimeT limitP);
