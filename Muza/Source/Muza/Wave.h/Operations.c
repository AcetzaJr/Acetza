#include "Muza/Panic.h"
#include "Muza/Wave.h"

#include "Muza/FrameRate.h"
#include "Muza/Types.h"

#include <stdlib.h>
#include <sys/param.h>

void MzWaveAddF(MzWaveZ *waveP, MzWaveZ *otherP, MzTimeT timeP,
                MzAmplitudeT amplitude) {
  MzIndexT startL = MzTimeToFrameF(timeP, waveP->frameRateM);
  MzIndexT endL = startL + otherP->framesM;
  if (endL > waveP->framesM) {
    MzWaveResizeFillF(waveP, endL, 0.0);
  }
  MzCountT channelsL = MIN(waveP->channelsM, otherP->channelsM);
  MzIndexT otherFrameL = 0;
  for (MzIndexT waveFrameL = startL; waveFrameL < endL;
       ++waveFrameL, ++otherFrameL) {
    for (MzIndexT channelL = 0; channelL < channelsL; ++channelL) {
      *MzWaveSampleF(waveP, waveFrameL, channelL) +=
          *MzWaveSampleF(otherP, otherFrameL, channelL) * amplitude;
    }
  }
}

void MzWaveResizeF(MzWaveZ *waveP, MzSizeT framesP) {
  waveP->framesM = framesP;
  MzSizeT sizeL = sizeof(MzSampleT) * framesP * waveP->channelsM;
  if (waveP->samplesM == NULL) {
    waveP->samplesM = malloc(sizeL);
  } else {
    waveP->samplesM = realloc(waveP->samplesM, sizeL);
  }
  if (waveP->samplesM == NULL) {
    MzPanicF(1, "could not resize the wave");
  }
}

void MzWaveResizeFillF(MzWaveZ *waveP, MzSizeT framesP, MzSampleT fillP) {
  MzSizeT oldSizeL = waveP->framesM;
  MzWaveResizeF(waveP, framesP);
  if (oldSizeL >= framesP) {
    return;
  }
  for (MzIndexT frameL = oldSizeL; frameL < waveP->framesM; ++frameL) {
    for (MzIndexT channelL = 0; channelL < waveP->channelsM; ++channelL) {
      *MzWaveSampleF(waveP, frameL, channelL) = fillP;
    }
  }
}

void MzWaveNormalizeF(MzWaveZ *waveP) {
  MzAmplitudeT maxL = MzWaveMaxF(waveP);
  if (maxL == 0.0) {
    return;
  }
  MzWaveMulF(waveP, 1.0 / maxL);
}

void MzWaveMulF(MzWaveZ *waveP, MzAmplitudeT amplitudeP) {
  for (MzIndexT indexL = 0; indexL < waveP->framesM * waveP->channelsM;
       ++indexL) {
    waveP->samplesM[indexL] *= amplitudeP;
  }
}
