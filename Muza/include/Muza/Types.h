#pragma once

#include "Muza/Common.h"

typedef f64 MzSampleT;

typedef f64 MzPartT;

typedef f64 MzAmplitudeT;

typedef f64 MzFrequencyT;

typedef f64 MzDurationT;

typedef f64 MzTimeT;

typedef f64 MzAttackT;

typedef f64 MzHoldT;

typedef f64 MzDecayT;

typedef f64 MzSustainT;

typedef f64 MzReleaseT;

typedef u64 MzChannelsT;

typedef u64 MzFrameRateT;

typedef u64 MzFramesT;

typedef u64 MzIndexT;

typedef u64 MzFrameT;

typedef u64 MzChannelT;

typedef u64 MzSizeT;

typedef u64 MzCountT;

typedef u64 MzDepthT;

typedef MzSampleT (*MzPrimitiveF)(MzPartT part);

typedef MzAmplitudeT (*MzTransformerF)(MzPartT part);

typedef MzIndexT (*MzNumbererF)(MzIndexT index);
