#include "Muza/Math.h"

#include "Muza/Common.h"

u64T MzPosModU64F(u64T numberP, u64T modulusP) {
  return numberP < 0 ? (numberP % modulusP + modulusP) % modulusP
                     : numberP % modulusP;
}
