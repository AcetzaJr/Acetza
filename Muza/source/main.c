#include "Muza/Blocks/Block.h"
#include "Muza/Blocks/Enveloper.h"
#include "Muza/Blocks/Harmonizer.h"
#include "Muza/Measure.h"
#include "Muza/Wave.h"

#include <stdio.h>

void fun(void * /*data*/) {
  printf("Hello Muza\n");
  MzWaveZ wave;

  MzBlockWave(&MzBlockR, &wave);
  MzWaveSave(&wave, "out/MzBlockR.wav");
  MzWaveFree(&wave);

  MzHarmonizerWave(&MzHarmonizerR, &wave);
  MzWaveSave(&wave, "out/MzHarmonizerR.wav");
  MzWaveFree(&wave);

  MzEnveloperWave(&MzEnveloperR, &wave);
  MzWaveSave(&wave, "out/MzEnveloperR.wav");
  MzWaveFree(&wave);
}

int main() { MzMeasure(fun, NULL); }
