#include "Muza/Printing.h"

#include "Muza/Common.h"

#include <stdio.h>

void MzU64PrintF(u64T numberP) {
  if (numberP < 1000) {
    printf("%ld", numberP);
    return;
  }
  MzU64PrintF(numberP / 1000);
  printf(",%03ld", numberP % 1000);
}
