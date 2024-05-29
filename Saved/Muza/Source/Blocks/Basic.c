
#include "Muza/Blocks/Basic.h"

#include "Muza/Functions/Primitives.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

#include <math.h>

MzBasicZ MzBasicG = {.primitiveM = MzPrimitivesSinF,
                     .frequencyM = 360,
                     .durationM = 1,
                     .amplitudeM = 1,
                     .channelsM = 2,
                     .frameRateM = 44'100};

void MzBasicCopyF(MzBasicZ *basicP, MzBasicZ *fromP) {
  basicP->primitiveM = fromP->primitiveM;
  basicP->frequencyM = fromP->frequencyM;
  basicP->durationM = fromP->durationM;
  basicP->amplitudeM = fromP->amplitudeM;
  basicP->channelsM = fromP->channelsM;
  basicP->frameRateM = fromP->frameRateM;
}

void MzBasicWaveF(MzBasicZ *basicP, MzWaveZ *waveP) {
  MzWaveWithDurationF(waveP, basicP->durationM, basicP->channelsM,
                      basicP->frameRateM);
  for (MzIndexT frameL = 0; frameL < waveP->framesM; ++frameL) {
    MzTimeT timeL = MzFrameToTimeF(frameL, waveP->frameRateM);
    MzPartT partL = fmod(timeL * basicP->frequencyM, 1.0);
    MzSampleT sampleL = basicP->primitiveM(partL) * basicP->amplitudeM;
    for (MzIndexT channelL = 0; channelL < waveP->channelsM; ++channelL) {
      *MzWaveSampleF(waveP, frameL, channelL) = sampleL;
    }
  }
}

MzFrequencyT MzBasicFrequencyF(MzBasicZ *basicP) { return basicP->frequencyM; }

void MzBasicSetFrequencyF(MzBasicZ *basicP, MzFrequencyT frequencyP) {
  basicP->frequencyM = frequencyP;
}

void MzBasicSetDurationF(MzBasicZ *basicP, MzDurationT durationP) {
  basicP->durationM = durationP;
}
