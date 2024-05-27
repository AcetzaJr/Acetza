#include "Muza/Wave.h"

#include "Muza/Types.h"

MzSampleT *MzWaveSample(MzWaveZ *wave, MzFrameT frame, MzChannelT channel) {
  return &wave->samples[frame * wave->channels + channel];
}

MzAmplitudeT MzWaveMax(MzWaveZ *wave) {
  MzAmplitudeT max = 0.0;
  for (MzIndexT index = 0; index < wave->frames * wave->channels; ++index) {
    if (wave->samples[index] > max) {
      max = wave->samples[index];
    }
  }
  return max;
}

MzDurationT MzWaveDuration(MzWaveZ *wave) {
  return MzFrameToTime(wave->frames, wave->frameRate);
}
