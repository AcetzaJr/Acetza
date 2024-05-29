#include "Muza/RT/Session.h"

#include "Muza/Panic.h"
#include "Muza/RT/AudioCallback.h"
#include "Muza/RT/MidiThread.h"
#include "Muza/RT/Util.h"
#include "Muza/RT/WaveBuffer.h"
#include "glib.h"

#include <portaudio.h>
#include <portmidi.h>

#include <stddef.h>
#include <stdio.h>
#include <threads.h>
#include <time.h>

int MzDefaultDeviceIDG = 3;
MzSessionZ MzSessionG = {
    .runningM = false, .channelsCountM = 2, .frameRateM = 44'100};

void MzSessionStartF() {
  MzInitRTF();
  PortMidiStream *streamL = MzOpenMidiInputF(MzDefaultDeviceIDG);
  MzSessionG.runningM = true;
  PaStream *audioStreamL;
  PaError errorL = Pa_OpenDefaultStream(
      &audioStreamL, 0, MzSessionG.channelsCountM, paFloat32,
      MzSessionG.frameRateM, paFramesPerBufferUnspecified, MzAudioCallbackF,
      NULL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not open audio stream");
  }
  const PaStreamInfo *info = Pa_GetStreamInfo(audioStreamL);
  // printf("outputLatency: %f\n", info->outputLatency);
  // printf("buffer: %f\n", info->outputLatency * 44'100 / 4);
  MzWaveBufferInitF(&MzSessionG.waveBufferM, 2,
                    info->outputLatency * MzSessionG.frameRateM /
                        MzSessionG.channelsCountM,
                    MzSessionG.channelsCountM);
  MzSessionG.blockQueueM = g_async_queue_new();
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
  MzWaveBufferFreeF(&MzSessionG.waveBufferM);
  g_async_queue_unref(MzSessionG.blockQueueM);
}
