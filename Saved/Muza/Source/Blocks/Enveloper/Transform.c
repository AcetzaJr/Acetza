#include "Muza/Blocks/Enveloper/Transform.h"

#include "Muza/Blocks/Enveloper.h"
#include "Muza/Common.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzUntilZ MzUntilReleaseF(MzEnveloperZ *enveloperP, MzWaveZ *waveP,
                         MzDurationT durationP) {
  MzUntilZ untilL;
  MzTimeT releaseStartL = durationP - enveloperP->releaseM;
  if (releaseStartL <= 0.0) {
    untilL.timeM = 0.0;
    untilL.amplitudeM = 1.0;
    return untilL;
  }
  MzTransformResultZ resultL;
  resultL = MzTransformF(waveP, enveloperP->attackTransformerM, 0.0, 0.0,
                         enveloperP->attackM, 1.0, releaseStartL);
  if (resultL.disruptedM) {
    untilL.timeM = releaseStartL;
    untilL.amplitudeM = resultL.amplitudeM;
    return untilL;
  }
  MzTimeT holdEndL = enveloperP->attackM + enveloperP->holdM;
  if (holdEndL >= releaseStartL) {
    untilL.timeM = releaseStartL;
    untilL.amplitudeM = 1.0;
    return untilL;
  }
  MzTimeT decayEndL = holdEndL + enveloperP->decayM;
  resultL = MzTransformF(waveP, enveloperP->decayTransformerM, holdEndL, 1.0,
                         decayEndL, enveloperP->sustainM, releaseStartL);
  if (resultL.disruptedM) {
    untilL.timeM = releaseStartL;
    untilL.amplitudeM = resultL.amplitudeM;
    return untilL;
  }
  MzIndexT startL = MzTimeToFrameF(decayEndL, waveP->frameRateM);
  MzIndexT endL = MzTimeToFrameF(releaseStartL, waveP->frameRateM);
  for (MzIndexT frameL = startL; frameL < endL; ++frameL) {
    for (MzIndexT channelL = 0; channelL < waveP->channelsM; ++channelL) {
      *MzWaveSampleF(waveP, frameL, channelL) *= enveloperP->sustainM;
    }
  }
  untilL.timeM = releaseStartL;
  untilL.amplitudeM = enveloperP->sustainM;
  return untilL;
}

MzTransformResultZ MzTransformF(MzWaveZ *waveP, MzTransformerT transformerP,
                                MzTimeT startTimeP,
                                MzAmplitudeT startAmplitudeP, MzTimeT endTimeP,
                                MzAmplitudeT endAmplitudeP, MzTimeT limitP) {
  MzIndexT frameLimitL = MzTimeToFrameF(limitP, waveP->frameRateM);
  MzIndexT startL = MzTimeToFrameF(startTimeP, waveP->frameRateM);
  MzIndexT endL = MzTimeToFrameF(endTimeP, waveP->frameRateM);
  MzAmplitudeT differenceL = endAmplitudeP - startAmplitudeP;
  MzAmplitudeT lastL = startAmplitudeP + transformerP(0.0) * differenceL;
  f64T framesL = (f64T)(endL - startL);
  MzTransformResultZ resultL;
  f64T indexL = 0.0;
  for (MzIndexT frameL = startL; frameL < endL; ++frameL, ++indexL) {
    if (frameL >= frameLimitL) {
      resultL.disruptedM = true;
      resultL.amplitudeM = lastL;
      resultL.timeM = MzFrameToTimeF(frameL, waveP->frameRateM);
      return resultL;
    }
    MzPartT partL = indexL / framesL;
    lastL = startAmplitudeP + transformerP(partL) * differenceL;
    for (MzIndexT channelL = 0; channelL < waveP->channelsM; ++channelL) {
      *MzWaveSampleF(waveP, frameL, channelL) *= lastL;
    }
  }
  resultL.disruptedM = false;
  resultL.amplitudeM = lastL;
  resultL.timeM = endTimeP;
  return resultL;
}
