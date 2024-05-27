#pragma once

#include "Muza/Types.h"

typedef struct {
  MzFramesT frames;
  MzChannelsT channelsM;
  MzFrameRateT frameRateM;
  MzSampleT *samples;
} MzWaveZ;

// Builders

void MzWaveWithDurationF(MzWaveZ *wave, MzDurationT duration,
                         MzChannelsT channels, MzFrameRateT frameRate);

void MzWaveEmptyF(MzWaveZ *wave, MzChannelsT channels, MzFrameRateT frameRate);

void MzWaveFreeF(MzWaveZ *wave);

// GETTERS

MzSampleT *MzWaveSampleF(MzWaveZ *wave, MzFrameT frame, MzChannelT channel);

MzAmplitudeT MzWaveMaxF(MzWaveZ *wave);

MzDurationT MzWaveDurationF(MzWaveZ *wave);

// Operations

void MzWaveNormalizeF(MzWaveZ *wave);

void MzWaveMulF(MzWaveZ *wave, MzAmplitudeT amplitude);

void MzWaveResizeF(MzWaveZ *wave, MzSizeT frames);

void MzWaveResizeFillF(MzWaveZ *wave, MzSizeT frames, MzSampleT fill);

void MzWaveAddF(MzWaveZ *wave, MzWaveZ *other, MzTimeT time,
                MzAmplitudeT amplitude);

// IO

void MzWaveSaveF(MzWaveZ *wave, const char *path);

// FrameRate

MzIndexT MzTimeToFrameF(MzTimeT time, MzFrameRateT frameRate);

MzTimeT MzFrameToTimeF(MzIndexT frame, MzFrameRateT frameRate);
