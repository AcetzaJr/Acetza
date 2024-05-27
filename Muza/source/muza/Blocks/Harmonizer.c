
#include "Muza/Blocks/Harmonizer.h"

#include "Muza/Blocks/Block.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

void MzHarmonizerWave(MzHarmonizerZ *harmonizer, MzWaveZ *wave) {
  MzBlockWave(harmonizer->block, wave);
  const MzFrequencyT frequency = MzBlockFrequency(harmonizer->block);
  for (MzIndexT index = 2; index - 1 < harmonizer->depth; ++index) {
    MzIndexT number = harmonizer->numberer(index);
    MzBlockSetFrequency(harmonizer->block, frequency * (MzFrequencyT)number);
    MzWaveZ tmp;
    MzBlockWave(harmonizer->block, &tmp);
    MzWaveAdd(wave, &tmp, 0.0, 1.0 / (MzAmplitudeT)number);
    MzWaveFree(&tmp);
  }
  MzBlockSetFrequency(harmonizer->block, frequency);
  MzWaveNormalize(wave);
}

MzFrequencyT MzHarmonizerFrequency(MzHarmonizerZ *harmonizer) {
  return MzBlockFrequency(harmonizer->block);
}

void MzHarmonizerSetFrequency(MzHarmonizerZ *harmonizer,
                              MzFrequencyT frequency) {
  MzBlockSetFrequency(harmonizer->block, frequency);
}

void MzHarmonizerSetDuration(MzHarmonizerZ *harmonizer, MzDurationT duration) {
  MzBlockSetDuration(harmonizer->block, duration);
}
