#include "Muza/Wave.h"

#include "Muza/Types.h"

MzIndexT MzTimeToFrameF(MzTimeT timeP, MzFrameRateT frameRateP) {
  return (MzIndexT)(timeP * ((MzTimeT)frameRateP));
}

MzTimeT MzFrameToTimeF(MzIndexT frameP, MzFrameRateT frameRateP) {
  return ((MzTimeT)frameP) / ((MzTimeT)frameRateP);
}
