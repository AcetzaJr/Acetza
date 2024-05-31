#include "Muza/RT/Session.h"

#include "Muza/Panic.h"
#include "Muza/RT/AudioCallback.h"
#include "Muza/RT/BlockThread.h"
#include "Muza/RT/MidiThread.h"
#include "Muza/RT/Synth/Basic.h"
#include "Muza/RT/Synth/Synth.h"
#include "Muza/RT/Util.h"
#include "Muza/RT/WaveBuffer.h"
#include "Muza/Scale.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"
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
  // MzSizeT bufferSizeL = 256;
  PaError errorL = Pa_OpenDefaultStream(
      &audioStreamL, 0, (int)MzSessionG.channelsCountM, paFloat32,
      (double)MzSessionG.frameRateM, paFramesPerBufferUnspecified,
      MzAudioCallbackF, NULL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not open audio stream");
  }
  const PaStreamInfo *info = Pa_GetStreamInfo(audioStreamL);
  // printf("outputLatency: %f\n", info->outputLatency);
  // printf("buffer: %f\n", info->outputLatency * 44'100 / 4);
  MzSizeT latencyL =
      (MzFramesT)(info->outputLatency * (double)MzSessionG.frameRateM /
                  (double)MzSessionG.channelsCountM);
  printf("latency %lu\n", latencyL);
  MzWaveBufferInitF(&MzSessionG.waveBufferM, 1, latencyL,
                    MzSessionG.channelsCountM);
  MzSessionG.blockQueueM = g_async_queue_new();
  MzSessionG.processingM = true;
  MzAcetzaInitF(MzEqualTemperedF(5, 440));
  MzEqualTemperedInitF(MzEqualTemperedF(5, 440));
  printf("base %f\n", MzAcetzaG.baseM);
  MzSessionG.synthM = MzSynthBasicCreate();
  MzWaveEmptyF(&MzSessionG.waveM, MzSessionG.channelsCountM,
               MzSessionG.frameRateM);
  GThread *blockThreadL = g_thread_new("Block", MzBlockHandlerF, NULL);
  errorL = Pa_StartStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not start audio stream");
  }
  PortMidiStream *streamL = MzOpenMidiInputF(MzDefaultDeviceIDG);
  MzSessionG.midiQueueM = g_async_queue_new();
  GThread *midiHandlerThreadL = g_thread_new("Handler", MzMidiHandlerF, NULL);
  GThread *midiDispatcherThreadL =
      g_thread_new("Dispatcher", MzMidiDispatcherF, streamL);
  printf("> Press enter to exit session...\n");
  while (getchar() != '\n') {
  }
  MzSessionG.runningM = false;
  g_thread_join(midiDispatcherThreadL);
  g_thread_join(midiHandlerThreadL);
  errorL = Pa_StopStream(audioStreamL);
  if (errorL != paNoError) {
    MzPanicF(1, "could not stop audio stream");
  }
  MzSessionG.processingM = false;
  g_thread_join(blockThreadL);
  Pm_Close(streamL);
  MzEndRTF();
  MzWaveBufferFreeF(&MzSessionG.waveBufferM);
  g_async_queue_unref(MzSessionG.blockQueueM);
  MzSynthFreeF(MzSessionG.synthM);
  if (MzSessionG.waveM.samplesM != NULL) {
    MzWaveSaveF(&MzSessionG.waveM, "out/wave.wav");
  }
  MzWaveFreeF(&MzSessionG.waveM);
}
