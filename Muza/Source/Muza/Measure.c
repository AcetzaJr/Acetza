#include "Muza/Measure.h"

#include "Muza/Printing.h"

#include <bits/time.h>
#include <stdio.h>
#include <time.h>

void MzMeasureF(void (*fnP)(void *), void *dataP) {
  struct timespec startL;
  struct timespec stopL;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startL);
  fnP(dataP);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stopL);
  long secondsL = stopL.tv_sec - startL.tv_sec;
  long nanoL = stopL.tv_nsec - startL.tv_nsec;
  printf("> Running time [seconds: ");
  MzU64PrintF(secondsL);
  printf(", nano: ");
  MzU64PrintF(nanoL);
  printf("]\n");
}
