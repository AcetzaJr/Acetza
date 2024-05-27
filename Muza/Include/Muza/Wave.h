#pragma once

#include "Muza/Types.h"

typedef struct {
  MzFramesT frames;
  MzChannelsT channels;
  MzFrameRateT frameRate;
  MzSampleT *samples;
} MzWaveZ;

// Builders

void MzWaveWithDuration(MzWaveZ *wave, MzDurationT duration,
                        MzChannelsT channels, MzFrameRateT frameRate);

void MzWaveEmpty(MzWaveZ *wave, MzChannelsT channels, MzFrameRateT frameRate);

void MzWaveFree(MzWaveZ *wave);

// GETTERS

MzSampleT *MzWaveSample(MzWaveZ *wave, MzFrameT frame, MzChannelT channel);

MzAmplitudeT MzWaveMax(MzWaveZ *wave);

MzDurationT MzWaveDuration(MzWaveZ *wave);

// Operations

void MzWaveNormalize(MzWaveZ *wave);

void MzWaveMul(MzWaveZ *wave, MzAmplitudeT amplitude);

void MzWaveResize(MzWaveZ *wave, MzSizeT frames);

void MzWaveResizeFill(MzWaveZ *wave, MzSizeT frames, MzSampleT fill);

void MzWaveAdd(MzWaveZ *wave, MzWaveZ *other, MzTimeT time,
               MzAmplitudeT amplitude);

// IO

void MzWaveSave(MzWaveZ *wave, const char *path);

// FrameRate

MzIndexT MzTimeToFrame(MzTimeT time, MzFrameRateT frameRate);

MzTimeT MzFrameToTime(MzIndexT frame, MzFrameRateT frameRate);
