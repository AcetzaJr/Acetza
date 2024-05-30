#pragma once

#include "Muza/Types.h"

MzIndexT MzTimeToFrameF(MzTimeT timeP, MzFrameRateT frameRateP);

MzTimeT MzFrameToTimeF(MzIndexT frameP, MzFrameRateT frameRateP);
