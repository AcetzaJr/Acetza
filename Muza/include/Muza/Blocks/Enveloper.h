#pragma once

#include "Muza/Blocks/Block.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

typedef struct {
  MzBlockZ *block;
  MzAttackT attack;
  MzHoldT hold;
  MzDecayT decay;
  MzSustainT sustain;
  MzReleaseT release;
  MzTransformerF attackTransformer;
  MzTransformerF decayTransformer;
  MzTransformerF releaseTransformer;
} MzEnveloperZ;

extern MzEnveloperZ MzEnveloperR;

void MzEnveloperCopy(MzEnveloperZ *enveloper, MzEnveloperZ *from);

void MzEnveloperWave(MzEnveloperZ *enveloper, MzWaveZ *wave);

MzFrequencyT MzEnveloperFrequency(MzEnveloperZ *enveloper);

void MzEnveloperSetFrequency(MzEnveloperZ *enveloper, MzFrequencyT frequency);

void MzEnveloperSetDuration(MzEnveloperZ *enveloper, MzDurationT duration);
