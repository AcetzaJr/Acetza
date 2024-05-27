#include "Muza/Panic.h"
#include "Muza/Wave.h"

#include "Muza/Types.h"

#include <stdlib.h>
#include <sys/param.h>

void MzWaveAddF(MzWaveZ *wave, MzWaveZ *other, MzTimeT time,
                MzAmplitudeT amplitude) {
  MzIndexT start = MzTimeToFrameF(time, wave->frameRateM);
  MzIndexT end = start + other->frames;
  if (end > wave->frames) {
    MzWaveResizeFillF(wave, end, 0.0);
  }
  MzCountT channels = MIN(wave->channelsM, other->channelsM);
  MzIndexT otherFrame = 0;
  for (MzIndexT waveFrame = start; waveFrame < end; ++waveFrame, ++otherFrame) {
    for (MzIndexT channel = 0; channel < channels; ++channel) {
      *MzWaveSampleF(wave, waveFrame, channel) +=
          *MzWaveSampleF(other, otherFrame, channel) * amplitude;
    }
  }
}

void MzWaveResizeF(MzWaveZ *wave, MzSizeT frames) {
  wave->frames = frames;
  MzSizeT size = sizeof(MzSampleT) * frames * wave->channelsM;
  MzSampleT *samples;
  if (wave->samples == NULL) {
    samples = malloc(size);
  } else {
    samples = realloc(wave->samples, size);
  }
  if (samples == NULL) {
    MzPanicF(1, "could not resize the wave");
  }
  wave->samples = samples;
}

void MzWaveResizeFillF(MzWaveZ *wave, MzSizeT frames, MzSampleT fill) {
  MzSizeT oldSize = wave->frames;
  MzWaveResizeF(wave, frames);
  if (oldSize >= frames) {
    return;
  }
  for (MzIndexT frame = oldSize; frame < wave->frames; ++frame) {
    for (MzIndexT channel = 0; channel < wave->channelsM; ++channel) {
      *MzWaveSampleF(wave, frame, channel) = fill;
    }
  }
}

void MzWaveNormalizeF(MzWaveZ *wave) {
  MzAmplitudeT max = MzWaveMaxF(wave);
  if (max == 0.0) {
    return;
  }
  MzAmplitudeT amplitude = 1.0 / max;
  MzWaveMulF(wave, amplitude);
}

void MzWaveMulF(MzWaveZ *wave, MzAmplitudeT amplitude) {
  for (MzIndexT index = 0; index < wave->frames * wave->channelsM; ++index) {
    wave->samples[index] *= amplitude;
  }
}
