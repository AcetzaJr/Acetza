#include "Muza/RT/Session.h"

#include "Muza/Panic.h"
#include "Muza/RT/AudioCallback.h"
#include "Muza/RT/BlockThread.h"
#include "Muza/RT/MidiThread.h"
#include "Muza/RT/Synth/Basic.h"
#include "Muza/RT/Synth/Synth.h"
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
MzSessionZ MzSessionG = {.processingM = false,
                         .runningM = false,
                         .channelsCountM = 2,
                         .frameRateM = 44'100};

void MzSessionStartF() {
  MzInitRTF();
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
  MzSessionG.processingM = true;
  MzSessionG.synthM = MzSynthBasicCreate();
  thrd_t blockThreadL;
  thrd_create(&blockThreadL, MzBlockHandlerF, NULL);
  errorL = Pa_StartStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not start audio stream");
  }
  PortMidiStream *streamL = MzOpenMidiInputF(MzDefaultDeviceIDG);
  MzSessionG.midiQueueM = g_async_queue_new();
  thrd_t midiHandlerThreadL;
  thrd_create(&midiHandlerThreadL, MzMidiHandlerF, NULL);
  thrd_t midiDispatcherThreadL;
  thrd_create(&midiDispatcherThreadL, MzMidiDispatcherF, streamL);
  printf("> Press enter to exit session...\n");
  while (getchar() != '\n') {
  }
  MzSessionG.runningM = false;
  thrd_join(midiDispatcherThreadL, NULL);
  thrd_join(midiHandlerThreadL, NULL);
  errorL = Pa_StopStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not stop audio stream");
  }
  MzSessionG.processingM = false;
  thrd_join(blockThreadL, NULL);
  Pm_Close(streamL);
  MzEndRTF();
  MzWaveBufferFreeF(&MzSessionG.waveBufferM);
  g_async_queue_unref(MzSessionG.blockQueueM);
  MzSynthFreeF(MzSessionG.synthM);
}
