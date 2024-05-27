#include "Muza/Panic.h"
#include "Muza/Wave.h"

#include "Muza/Types.h"

#include <stdlib.h>
#include <sys/param.h>

void MzWaveAdd(MzWaveZ *wave, MzWaveZ *other, MzTimeT time,
               MzAmplitudeT amplitude) {
  MzIndexT start = MzTimeToFrame(time, wave->frameRate);
  MzIndexT end = start + other->frames;
  if (end > wave->frames) {
    MzWaveResizeFill(wave, end, 0.0);
  }
  MzCountT channels = MIN(wave->channels, other->channels);
  MzIndexT otherFrame = 0;
  for (MzIndexT waveFrame = start; waveFrame < end; ++waveFrame, ++otherFrame) {
    for (MzIndexT channel = 0; channel < channels; ++channel) {
      *MzWaveSample(wave, waveFrame, channel) +=
          *MzWaveSample(other, otherFrame, channel) * amplitude;
    }
  }
}

void MzWaveResize(MzWaveZ *wave, MzSizeT frames) {
  wave->frames = frames;
  MzSizeT size = sizeof(MzSampleT) * frames * wave->channels;
  MzSampleT *samples;
  if (wave->samples == NULL) {
    samples = malloc(size);
  } else {
    samples = realloc(wave->samples, size);
  }
  if (samples == NULL) {
    MzPanic(1, "could not resize the wave");
  }
  wave->samples = samples;
}

void MzWaveResizeFill(MzWaveZ *wave, MzSizeT frames, MzSampleT fill) {
  MzSizeT oldSize = wave->frames;
  MzWaveResize(wave, frames);
  if (oldSize >= frames) {
    return;
  }
  for (MzIndexT frame = oldSize; frame < wave->frames; ++frame) {
    for (MzIndexT channel = 0; channel < wave->channels; ++channel) {
      *MzWaveSample(wave, frame, channel) = fill;
    }
  }
}

void MzWaveNormalize(MzWaveZ *wave) {
  MzAmplitudeT max = MzWaveMax(wave);
  if (max == 0.0) {
    return;
  }
  MzAmplitudeT amplitude = 1.0 / max;
  MzWaveMul(wave, amplitude);
}

void MzWaveMul(MzWaveZ *wave, MzAmplitudeT amplitude) {
  for (MzIndexT index = 0; index < wave->frames * wave->channels; ++index) {
    wave->samples[index] *= amplitude;
  }
}
