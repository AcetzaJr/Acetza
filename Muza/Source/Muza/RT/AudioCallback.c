#include "Muza/RT/AudioCallback.h"

#include "Muza/RT/Session.h"
#include "Muza/RT/WaveBuffer.h"
#include "Muza/Types.h"

#include <portaudio.h>
// #include <stdio.h>

int MzAudioCallbackF(const void * /*inputP*/, void *outputP,
                     unsigned long framesCountP,
                     const PaStreamCallbackTimeInfo * /*timeInfoP*/,
                     PaStreamCallbackFlags /*statusFlagsP*/,
                     void * /*userDataP*/) {
  float *outputL = (float *)outputP;
  MzIndexT sampleIndex = 0;
  for (unsigned long frameL = 0; frameL < framesCountP; frameL++) {
    for (MzIndexT channelL = 0; channelL < MzSessionG.channelsCountM;
         channelL++) {
      outputL[sampleIndex++] = MzWaveBufferNextSampleF(&MzSessionG.waveBufferM);
      // outputL[sampleIndex++] = 0;
    }
  }
  return 0;
}
