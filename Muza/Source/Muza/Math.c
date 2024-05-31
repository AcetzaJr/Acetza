#include "Muza/Math.h"

#include "Muza/Common.h"
#include "Muza/Types.h"

#include <math.h>

i64T MzPosModi64F(i64T numberP, i64T modulusP) {
  return numberP < 0 ? (numberP % modulusP + modulusP) % modulusP
                     : numberP % modulusP;
}

MzDBT MzToDBF(MzAmplitudeT amplitudeP) { return 10 * log10(amplitudeP); }

MzAmplitudeT MzFromDBF(MzDBT dbP) { return pow(10, dbP / 10); }
