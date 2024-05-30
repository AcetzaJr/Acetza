#include "Muza/Math.h"

#include "Muza/Common.h"

i64T MzPosModi64F(i64T numberP, i64T modulusP) {
  return numberP < 0 ? (numberP % modulusP + modulusP) % modulusP
                     : numberP % modulusP;
}
