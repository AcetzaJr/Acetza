
#include "Muza/Blocks/Basic.h"

#include "Muza/Functions/Primitives.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

#include <math.h>

MzBasicZ MzBasicR = {.primitive = MzPrimitivesSin,
                     .frequency = 360,
                     .duration = 1,
                     .amplitude = 1,
                     .channels = 2,
                     .frameRate = 44'100};

void MzBasicCopy(MzBasicZ *basic, MzBasicZ *from) {
  basic->primitive = from->primitive;
  basic->frequency = from->frequency;
  basic->duration = from->duration;
  basic->amplitude = from->amplitude;
  basic->channels = from->channels;
  basic->frameRate = from->frameRate;
}

void MzBasicWave(MzBasicZ *basic, MzWaveZ *wave) {
  MzWaveWithDuration(wave, basic->duration, basic->channels, basic->frameRate);
  for (MzIndexT frame = 0; frame < wave->frames; ++frame) {
    MzTimeT time = MzFrameToTime(frame, wave->frameRate);
    MzPartT part = fmod(time * basic->frequency, 1.0);
    MzSampleT sample = basic->primitive(part) * basic->amplitude;
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
