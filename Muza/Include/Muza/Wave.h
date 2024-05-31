#pragma once

#include "Muza/RT/BufferBlock.h"
#include "Muza/Types.h"

typedef struct {
  MzFramesT framesM;
  MzChannelsT channelsM;
  MzFrameRateT frameRateM;
  MzSampleT *samplesM;
} MzWaveZ;

// Builders

void MzWaveWithDurationF(MzWaveZ *waveP, MzDurationT durationP,
                         MzChannelsT channelsP, MzFrameRateT frameRateP);

void MzWaveEmptyF(MzWaveZ *waveP, MzChannelsT channelsP,
                  MzFrameRateT frameRateP);

void MzWaveFreeF(MzWaveZ *waveP);

// GETTERS

MzSampleT *MzWaveSampleF(MzWaveZ *waveP, MzFrameT frameP, MzChannelT channelP);

MzAmplitudeT MzWaveMaxF(MzWaveZ *waveP);

MzDurationT MzWaveDurationF(MzWaveZ *waveP);

// Operations

void MzWaveAppendBlockF(MzWaveZ *waveP, MzBufferBlockZ *blockP);

void MzWaveNormalizeF(MzWaveZ *waveP);

void MzWaveMulF(MzWaveZ *waveP, MzAmplitudeT amplitudeP);

void MzWaveResizeF(MzWaveZ *waveP, MzSizeT framesP);

void MzWaveResizeFillF(MzWaveZ *waveP, MzSizeT framesP, MzSampleT fillP);

void MzWaveAddF(MzWaveZ *waveP, MzWaveZ *otherP, MzTimeT timeP,
                MzAmplitudeT amplitudeP);

// IO

void MzWaveSaveF(MzWaveZ *waveP, const char *pathP);
