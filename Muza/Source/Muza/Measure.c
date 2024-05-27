#include "Muza/Measure.h"

#include "Muza/Printing.h"

#include <bits/time.h>
#include <stdio.h>
#include <time.h>

void MzMeasure(void (*fun)(void *), void *data) {
  struct timespec start;
  struct timespec stop;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  fun(data);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  long seconds = stop.tv_sec - start.tv_sec;
  long nano = stop.tv_nsec - start.tv_nsec;
  printf("> Running time [seconds: ");
  MzU64Print(seconds);
  printf(", nano: ");
  MzU64Print(nano);
  printf("]\n");
}
