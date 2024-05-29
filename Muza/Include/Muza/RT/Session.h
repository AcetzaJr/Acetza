#pragma once

#include "Muza/RT/WaveBuffer.h"
#include "Muza/Types.h"

#include <glib.h>

typedef struct {
  GAsyncQueue *blockQueueM;
  MzWaveBufferZ waveBufferM;
  MzFrameRateT frameRateM;
  MzChannelsT channelsCountM;
  bool runningM;
} MzSessionZ;

extern MzSessionZ MzSessionG;

void MzSessionStartF();
