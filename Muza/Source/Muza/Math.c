#include "Muza/Math.h"

#include "Muza/Common.h"

u64 AzPosModU64(u64 number, u64 modulus) {
  return number < 0 ? (number % modulus + modulus) % modulus : number % modulus;
}
