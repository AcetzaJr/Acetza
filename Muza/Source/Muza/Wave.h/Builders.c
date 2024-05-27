#include "Muza/Wave.h"

#include "Muza/Types.h"

#include <stdlib.h>

void MzWaveWithDurationF(MzWaveZ *wave, MzDurationT duration,
                         MzChannelsT channels, MzFrameRateT frameRate) {
  wave->frames = MzTimeToFrameF(duration, frameRate);
  wave->channelsM = channels;
  wave->frameRateM = frameRate;
  MzSizeT size = sizeof(MzSampleT) * wave->frames * channels;
  if (size == 0) {
    wave->samples = NULL;
    return;
  }
  wave->samples = malloc(size);
}

void MzWaveEmptyF(MzWaveZ *wave, MzChannelsT channels, MzFrameRateT frameRate) {
  wave->frames = 0;
  wave->channelsM = channels;
  wave->frameRateM = frameRate;
  wave->samples = NULL;
}

void MzWaveFreeF(MzWaveZ *wave) { free(wave->samples); }
