
#include "Muza/Blocks/Basic.h"

#include "Muza/Types.h"
#include "Muza/Wave.h"

#include <math.h>

void MzBasicWave(MzBasicZ *basic, MzWaveZ *wave) {
  MzWaveWithDuration(wave, basic->duration, basic->channels, basic->frameRate);
  for (MzIndexT frame = 0; frame < wave->frames; ++frame) {
    MzTimeT time = MzFrameToTime(frame, wave->frameRate);
    MzPartT part = fmod(time * basic->frequency, 1.0);
    MzSampleT sample = basic->primitive(part);
    for (MzIndexT channel = 0; channel < wave->channels; ++channel) {
      *MzWaveSample(wave, frame, channel) = sample;
    }
  }
}

MzFrequencyT MzBasicFrequency(MzBasicZ *basic) { return basic->frequency; }

void MzBasicSetFrequency(MzBasicZ *basic, MzFrequencyT frequency) {
  basic->frequency = frequency;
}

void MzBasicSetDuration(MzBasicZ *basic, MzDurationT duration) {
  basic->duration = duration;
}
