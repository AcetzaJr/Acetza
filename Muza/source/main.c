#include <stdio.h>

#include "muza/measure.h"

void fn(void *) { printf("Hello Muza\n"); }

int main() { MzMeasure(fn, NULL); }
