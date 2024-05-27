#include "Muza/Functions/Transformers.h"

#include "Muza/Constants.h"
#include "Muza/Types.h"

#include <math.h>

MzAmplitudeT MzTransformersSmooth(MzPartT part) { return sin(HalfPiK * part); }

MzAmplitudeT MzTransformersSmoothInverse(MzPartT part) {
  return sin(HalfPiK * part + HalfPiK);
}
