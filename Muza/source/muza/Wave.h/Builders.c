#include "Muza/Wave.h"

#include "Muza/Types.h"

#include <stdlib.h>

void MzWaveWithDuration(MzWaveZ *wave, MzDurationT duration,
                        MzChannelsT channels, MzFrameRateT frameRate) {
  wave->frames = MzTimeToFrame(duration, frameRate);
  wave->channels = channels;
  wave->frameRate = frameRate;
  MzSizeT size = sizeof(MzSampleT) * wave->frames * channels;
  if (size == 0) {
    wave->samples = NULL;
    return;
  }
  wave->samples = malloc(size);
}

void MzWaveEmpty(MzWaveZ *wave, MzChannelsT channels, MzFrameRateT frameRate) {
  wave->frames = 0;
  wave->channels = channels;
  wave->frameRate = frameRate;
  wave->samples = NULL;
}

void MzWaveFree(MzWaveZ *wave) { free(wave->samples); }
