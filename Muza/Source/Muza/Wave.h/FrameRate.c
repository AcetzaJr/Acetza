#include "Muza/Wave.h"

#include "Muza/Types.h"

MzIndexT MzTimeToFrameF(MzTimeT time, MzFrameRateT frameRate) {
  return (MzIndexT)(time * ((MzTimeT)frameRate));
}

MzTimeT MzFrameToTimeF(MzIndexT frame, MzFrameRateT frameRate) {
  return ((MzTimeT)frame) / ((MzTimeT)frameRate);
}
