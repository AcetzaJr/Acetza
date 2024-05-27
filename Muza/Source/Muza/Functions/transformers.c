#include "Muza/Functions/Transformers.h"

#include "Muza/Constants.h"
#include "Muza/Types.h"

#include <math.h>

MzAmplitudeT MzTransformersSmoothF(MzPartT partP) {
  return sin(HalfPiK * partP);
}

MzAmplitudeT MzTransformersSmoothInverseF(MzPartT partP) {
  return sin(HalfPiK * partP + HalfPiK);
}
