#include "Muza/Blocks/Block.h"
#include "Muza/Blocks/Enveloper.h"
#include "Muza/Blocks/Harmonizer.h"
#include "Muza/Measure.h"
#include "Muza/Wave.h"

#include <stdio.h>

void Test1F(void * /*data*/) {
  printf("Hello Muza\n");
  MzWaveZ waveL;

  MzBlockWaveF(&MzBlockG, &waveL);
  MzWaveSaveF(&waveL, "out/MzBlockR.wav");
  MzWaveFreeF(&waveL);

  MzHarmonizerWaveF(&MzHarmonizerG, &waveL);
  MzWaveSaveF(&waveL, "out/MzHarmonizerR.wav");
  MzWaveFreeF(&waveL);

  MzEnveloperWaveF(&MzEnveloperG, &waveL);
  MzWaveSaveF(&waveL, "out/MzEnveloperR.wav");
  MzWaveFreeF(&waveL);
}

int main() { MzMeasureF(Test1F, NULL); }
