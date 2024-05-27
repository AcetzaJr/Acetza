#include "Muza/Blocks/Enveloper/Transform.h"

#include "Muza/Blocks/Enveloper.h"
#include "Muza/Common.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzUntilZ MzUntilRelease(MzEnveloperZ *enveloper, MzWaveZ *wave,
                        MzDurationT duration) {
  MzUntilZ until;
  MzTimeT releaseStart = duration - enveloper->release;
  if (releaseStart <= 0.0) {
    until.time = 0.0;
    until.amplitude = 1.0;
    return until;
  }
  MzTransformResultZ result;
  result = MzTransform(wave, enveloper->attackTransformer, 0.0, 0.0,
                       enveloper->attack, 1.0, releaseStart);
  if (result.disrupted) {
    until.time = releaseStart;
    until.amplitude = result.amplitude;
    return until;
  }
  MzTimeT holdEnd = enveloper->attack + enveloper->hold;
  if (holdEnd >= releaseStart) {
    until.time = releaseStart;
    until.amplitude = 1.0;
    return until;
  }
  MzTimeT decayEnd = holdEnd + enveloper->decay;
  result = MzTransform(wave, enveloper->decayTransformer, holdEnd, 1.0,
                       decayEnd, enveloper->sustain, releaseStart);
  if (result.disrupted) {
    until.time = releaseStart;
    until.amplitude = result.amplitude;
    return until;
  }
  MzIndexT start = MzTimeToFrame(decayEnd, wave->frameRate);
  MzIndexT end = MzTimeToFrame(releaseStart, wave->frameRate);
  for (MzIndexT frame = start; frame < end; ++frame) {
    for (MzIndexT channel = 0; channel < wave->channels; ++channel) {
      *MzWaveSample(wave, frame, channel) *= enveloper->sustain;
    }
  }
  until.time = releaseStart;
  until.amplitude = enveloper->sustain;
  return until;
}

MzTransformResultZ MzTransform(MzWaveZ *wave, MzTransformerF transformer,
                               MzTimeT startTime, MzAmplitudeT startAmplitude,
                               MzTimeT endTime, MzAmplitudeT endAmplitude,
                               MzTimeT limit) {
  MzIndexT frameLimit = MzTimeToFrame(limit, wave->frameRate);
  MzIndexT start = MzTimeToFrame(startTime, wave->frameRate);
  MzIndexT end = MzTimeToFrame(endTime, wave->frameRate);
  MzAmplitudeT difference = endAmplitude - startAmplitude;
  MzAmplitudeT last = startAmplitude + transformer(0.0) * difference;
  f64 frames = (f64)(end - start);
  MzTransformResultZ result;
  f64 index = 0.0;
  for (MzIndexT frame = start; frame < end; ++frame, ++index) {
    if (frame >= frameLimit) {
      result.disrupted = true;
      result.amplitude = last;
      result.time = MzFrameToTime(frame, wave->frameRate);
      return result;
    }
    MzPartT part = index / frames;
    last = startAmplitude + transformer(part) * difference;
    for (MzIndexT channel = 0; channel < wave->channels; ++channel) {
      *MzWaveSample(wave, frame, channel) *= last;
    }
  }
  result.disrupted = false;
  result.amplitude = last;
  result.time = endTime;
  return result;
}
