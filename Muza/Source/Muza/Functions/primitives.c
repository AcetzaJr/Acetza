#include "Muza/Functions/Primitives.h"

#include "Muza/Constants.h"
#include "Muza/Types.h"

#include <math.h>

MzSampleT MzPrimitivesSawF(MzPartT partP) { return 1.0 - 2.0 * partP; }

MzSampleT MzPrimitivesSqrF(MzPartT partP) { return partP < 0.5 ? 1.0 : -1.0; }

MzSampleT MzPrimitivesTriF(MzPartT partP) {
  if (partP < 0.25) {
    return 4.0 * partP;
  }
  if (partP < 0.75) {
    return 2.0 - 4.0 * partP;
  }
  return 4.0 * partP - 4.0;
}

MzSampleT MzPrimitivesSinF(MzPartT partP) { return sin(TwoPiK * partP); }
