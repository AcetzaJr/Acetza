#include "Muza/RT/Effects/HardLimit.h"

#include "Muza/Types.h"

// #include <stdio.h>

void MzHardLimitF(MzBufferBlockZ *blockP) {
  for (MzIndexT indexL = 0; indexL < blockP->samplesCountM; indexL++) {
    MzSampleT *sampleL = &blockP->samplesM[indexL];
    if (*sampleL < -1) {
      *sampleL = -1;
      // printf("MzHardLimitF\n");
    } else if (*sampleL > 1) {
      *sampleL = 1;
      // printf("MzHardLimitF\n");
    }
  }
}
