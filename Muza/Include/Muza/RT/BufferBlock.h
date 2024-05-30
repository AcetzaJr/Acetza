#pragma once

#include "Muza/Types.h"

#include <glib.h>

typedef struct {
  GMutex samplesMutexM;
  MzSampleT *samplesM;
  MzCountT samplesCountM;
  MzFramesT framesCountM;
  MzChannelsT channelsCountM;
  bool isReadyM;
} MzBufferBlockZ;

MzBufferBlockZ *MzBufferBlockCreateF(MzFramesT framesCountP,
                                     MzChannelsT channelsCountP);

void MzBufferBlockInitF(MzBufferBlockZ *blockP, MzFramesT framesCountP,
                        MzChannelsT channelsCountP);

void MzBufferBlockFreeF(MzBufferBlockZ *blockP);

void MzBufferBlockNotReadyF(MzBufferBlockZ *blockP);

MzSampleT *MzBufferBlockLock(MzBufferBlockZ *blockP, MzFrameT frameP,
                             MzChannelT channelP);

void MzBufferBlockUnLock(MzBufferBlockZ *blockP);
