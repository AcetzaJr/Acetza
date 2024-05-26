#include "muza/measure.h"

#include "muza/printing.h"

#include <bits/time.h>
#include <stdio.h>
#include <time.h>

void MzMeasure(void (*fn)(void *), void *data) {
  struct timespec start;
  struct timespec stop;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  fn(data);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  long seconds = stop.tv_sec - start.tv_sec;
  long nano = stop.tv_nsec - start.tv_nsec;
  printf("> Running time [seconds: ");
  MzU64Print(seconds);
  printf(", nano: ");
  MzU64Print(nano);
  printf("]\n");
}
