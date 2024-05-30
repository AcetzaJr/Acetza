#include "Muza/Wave.h"

#include "Muza/FrameRate.h"
#include "Muza/Types.h"

MzSampleT *MzWaveSampleF(MzWaveZ *waveP, MzFrameT frameP, MzChannelT channelP) {
  return &waveP->samplesM[frameP * waveP->channelsM + channelP];
}

MzAmplitudeT MzWaveMaxF(MzWaveZ *waveP) {
  MzAmplitudeT maxL = 0.0;
  for (MzIndexT indexL = 0; indexL < waveP->framesM * waveP->channelsM;
       ++indexL) {
    if (waveP->samplesM[indexL] > maxL) {
      maxL = waveP->samplesM[indexL];
    }
  }
  return maxL;
}

MzDurationT MzWaveDurationF(MzWaveZ *waveP) {
  return MzFrameToTimeF(waveP->framesM, waveP->frameRateM);
}
