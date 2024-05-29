#include "Muza/RT/Session.h"

#include "Muza/Panic.h"
#include "Muza/RT/AudioCallback.h"
#include "Muza/RT/MidiThread.h"
#include "Muza/RT/Util.h"

#include <portaudio.h>
#include <portmidi.h>

#include <stddef.h>
#include <stdio.h>
#include <threads.h>
#include <time.h>

int MzDefaultDeviceIDG = 3;
MzSessionZ MzSessionG = {.runningM = false};

void MzSessionStartF() {
  MzInitRTF();
  PortMidiStream *streamL = MzOpenMidiInputF(MzDefaultDeviceIDG);
  MzSessionG.runningM = true;
  PaStream *audioStreamL;
  PaError errorL = Pa_OpenDefaultStream(&audioStreamL, 0, 2, paFloat32, 44'100,
                                        paFramesPerBufferUnspecified,
                                        MzAudioCallbackF, NULL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not open audio stream");
  }
  const PaStreamInfo *info = Pa_GetStreamInfo(audioStreamL);
  printf("outputLatency: %f\n", info->outputLatency);
  printf("buffer: %f\n", info->outputLatency * 44'100 / 4);
  errorL = Pa_StartStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not start audio stream");
  }
  thrd_t threadL;
  thrd_create(&threadL, MzMidiHandlerF, streamL);
  printf("> Press enter to exit session...\n");
  while (getchar() != '\n') {
  }
  MzSessionG.runningM = false;
  thrd_join(threadL, NULL);
  errorL = Pa_StopStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not stop audio stream");
  }
  Pm_Close(streamL);
  MzEndRTF();
}
