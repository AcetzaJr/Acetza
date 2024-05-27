#include "Muza/Wave.h"

#include "Muza/Types.h"

MzIndexT MzTimeToFrame(MzTimeT time, MzFrameRateT frameRate) {
  return (MzIndexT)(time * ((MzTimeT)frameRate));
}

MzTimeT MzFrameToTime(MzIndexT frame, MzFrameRateT frameRate) {
  return ((MzTimeT)frame) / ((MzTimeT)frameRate);
}
