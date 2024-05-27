#include "Muza/Blocks/Enveloper.h"

#include "Muza/Blocks/Block.h"
#include "Muza/Blocks/Enveloper/Transform.h"
#include "Muza/Functions/Transformers.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzEnveloperZ MzEnveloperR = {.block = &MzBlockR,
                             .attack = 1.0 / 16.0,
                             .hold = 1.0 / 12.0,
                             .decay = 1.0 / 8.0,
                             .sustain = 1.0 / 2.0,
                             .release = 1.0 / 4.0,
                             .attackTransformer = MzTransformersSmooth,
                             .decayTransformer = MzTransformersSmooth,
                             .releaseTransformer = MzTransformersSmooth};

void MzEnveloperCopy(MzEnveloperZ *enveloper, MzEnveloperZ *from) {
  enveloper->block = from->block;
  enveloper->attack = from->attack;
  enveloper->hold = from->hold;
  enveloper->decay = from->decay;
  enveloper->sustain = from->sustain;
  enveloper->release = from->release;
  enveloper->attackTransformer = from->attackTransformer;
  enveloper->decayTransformer = from->decayTransformer;
  enveloper->releaseTransformer = from->releaseTransformer;
}

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
