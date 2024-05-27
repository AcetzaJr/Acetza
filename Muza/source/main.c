#include "Muza/Blocks/Basic.h"
#include "Muza/Functions/Primitives.h"
#include "Muza/Measure.h"
#include "Muza/Wave.h"

#include <stdio.h>

void fun(void * /*data*/) {
  printf("Hello Muza\n");
  MzBasicZ basic = {.primitive = MzPrimitivesSin,
                    .frequency = 360,
                    .duration = 1,
                    .channels = 2,
                    .frameRate = 44'100};
  MzWaveZ wave;
  MzBasicWave(&basic, &wave);
  MzWaveSave(&wave, "out/wave.wav");
}

int main() { MzMeasure(fun, NULL); }
