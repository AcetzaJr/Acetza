#include "Muza/Wave.h"

#include "Muza/FrameRate.h"
#include "Muza/Types.h"

#include <stdlib.h>

void MzWaveWithDurationF(MzWaveZ *waveP, MzDurationT durationP,
                         MzChannelsT channelsP, MzFrameRateT frameRateP) {
  waveP->framesM = MzTimeToFrameF(durationP, frameRateP);
  waveP->channelsM = channelsP;
  waveP->frameRateM = frameRateP;
  MzSizeT sizeL = sizeof(MzSampleT) * waveP->framesM * channelsP;
  if (sizeL == 0) {
    waveP->samplesM = NULL;
    return;
  }
  waveP->samplesM = malloc(sizeL);
}

void MzWaveEmptyF(MzWaveZ *waveP, MzChannelsT channelsP,
                  MzFrameRateT frameRateP) {
  waveP->framesM = 0;
  waveP->channelsM = channelsP;
  waveP->frameRateM = frameRateP;
  waveP->samplesM = NULL;
}

void MzWaveFreeF(MzWaveZ *waveP) { free(waveP->samplesM); }
