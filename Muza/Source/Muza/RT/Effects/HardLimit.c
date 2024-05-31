#include "Muza/RT/Effects/HardLimit.h"
#include "Muza/Types.h"

void MzHardLimitF(MzBufferBlockZ *blockP) {
  for (MzIndexT indexL = 0; indexL < blockP->samplesCountM; indexL++) {
    MzSampleT *sampleL = &blockP->samplesM[indexL];
    if (*sampleL < -1) {
      *sampleL = -1;
    } else if (*sampleL > 1) {
      *sampleL = 1;
    }
  }
}
