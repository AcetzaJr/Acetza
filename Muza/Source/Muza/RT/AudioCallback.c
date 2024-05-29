#include "Muza/RT/AudioCallback.h"

#include <portaudio.h>
// #include <stdio.h>

int MzAudioCallbackF(const void * /*inputP*/, void * /*outputP*/,
                     unsigned long /*framesCountP*/,
                     const PaStreamCallbackTimeInfo * /*timeInfoP*/,
                     PaStreamCallbackFlags /*statusFlagsP*/,
                     void * /*userDataP*/) {
  // printf("%lu\n", framesCountP);
  // fflush(stdout);
  return 0;
}
