#pragma once

#include "Muza/RT/Synth/Synth.h"
#include "Muza/RT/WaveBuffer.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

#include <glib.h>

typedef struct {
  MzWaveZ waveM;
  GAsyncQueue *blockQueueM;
  GAsyncQueue *midiQueueM;
  MzWaveBufferZ waveBufferM;
  MzSynthZ *synthM;
  MzFrameRateT frameRateM;
  MzChannelsT channelsCountM;
  bool runningM;
  bool processingM;
} MzSessionZ;

extern MzSessionZ MzSessionG;

void MzSessionStartF();
