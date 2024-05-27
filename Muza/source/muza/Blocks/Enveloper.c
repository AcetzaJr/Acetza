#include "Muza/Blocks/Enveloper.h"

#include "Muza/Blocks/Block.h"
#include "Muza/Blocks/Enveloper/Transform.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

void MzEnveloperWave(MzEnveloperZ *enveloper, MzWaveZ *wave) {
  MzBlockWave(enveloper->block, wave);
  MzDurationT duration = MzWaveDuration(wave);
  MzUntilZ until = MzUntilRelease(enveloper, wave, duration);
  MzTransform(wave, enveloper->releaseTransformer, until.time, until.amplitude,
              duration, 0.0, duration);
}

MzFrequencyT MzEnveloperFrequency(MzEnveloperZ *enveloper) {
  return MzBlockFrequency(enveloper->block);
}

void MzEnveloperSetFrequency(MzEnveloperZ *enveloper, MzFrequencyT frequency) {
  MzBlockSetFrequency(enveloper->block, frequency);
}

void MzEnveloperSetDuration(MzEnveloperZ *enveloper, MzDurationT duration) {
  MzBlockSetDuration(enveloper->block, duration);
}
