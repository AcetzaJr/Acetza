#include "Muza/Functions/Primitives.h"

#include "Muza/Constants.h"
#include "Muza/Types.h"

#include <math.h>

MzSampleT MzPrimitivesSaw(MzPartT part) { return 1.0 - 2.0 * part; }

MzSampleT MzPrimitivesSqr(MzPartT part) { return part < 0.5 ? 1.0 : -1.0; }

MzSampleT MzPrimitivesTri(MzPartT part) {
  if (part < 0.25) {
    return 4.0 * part;
  }
  if (part < 0.75) {
    return 2.0 - 4.0 * part;
  }
  return 4.0 * part - 4.0;
}

MzSampleT MzPrimitivesSin(MzPartT part) { return sin(TwoPiK * part); }
