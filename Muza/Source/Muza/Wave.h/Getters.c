#include "Muza/Wave.h"

#include "Muza/Types.h"

MzSampleT *MzWaveSampleF(MzWaveZ *wave, MzFrameT frame, MzChannelT channel) {
  return &wave->samples[frame * wave->channelsM + channel];
}

MzAmplitudeT MzWaveMaxF(MzWaveZ *wave) {
  MzAmplitudeT max = 0.0;
  for (MzIndexT index = 0; index < wave->frames * wave->channelsM; ++index) {
    if (wave->samples[index] > max) {
      max = wave->samples[index];
    }
  }
  return max;
}

MzDurationT MzWaveDurationF(MzWaveZ *wave) {
  return MzFrameToTimeF(wave->frames, wave->frameRateM);
}
