#pragma once

#include "Muza/Types.h"
typedef struct {
  MzFrameRateT frameRateM;
  MzChannelsT channelsCountM;
  bool runningM;
} MzSessionZ;

extern MzSessionZ MzSessionG;

void MzSessionStartF();
