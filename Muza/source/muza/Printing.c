#include "Muza/Printing.h"

#include "Muza/Common.h"

#include <stdio.h>

void MzU64Print(u64 n) {
  if (n < 1000) {
    printf("%ld", n);
    return;
  }
  MzU64Print(n / 1000);
  printf(",%03ld", n % 1000);
}
