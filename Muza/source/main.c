#include <stdio.h>

#include "Muza/Measure.h"

void fun(void * /*data*/) { printf("Hello Muza\n"); }

int main() { MzMeasure(fun, NULL); }
