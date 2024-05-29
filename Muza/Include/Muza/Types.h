#pragma once

#include "Muza/Common.h"

typedef f64T MzSampleT;

typedef f64T MzPartT;

typedef f64T MzAmplitudeT;

typedef f64T MzFrequencyT;

typedef f64T MzDurationT;

typedef f64T MzTimeT;

typedef f64T MzAttackT;

typedef f64T MzHoldT;

typedef f64T MzDecayT;

typedef f64T MzSustainT;

typedef f64T MzReleaseT;

typedef u64T MzChannelsT;

typedef u64T MzFrameRateT;

typedef u64T MzFramesT;

typedef u64T MzIndexT;

typedef u64T MzFrameT;

typedef u64T MzChannelT;

typedef u64T MzSizeT;

typedef u64T MzCountT;

typedef u64T MzDepthT;

typedef i64T MzNoteT;

typedef i64T MzSIndexT;

typedef MzSampleT (*MzPrimitiveFT)(MzPartT part);

typedef MzAmplitudeT (*MzTransformerFT)(MzPartT part);

typedef MzIndexT (*MzNumbererFT)(MzIndexT index);
