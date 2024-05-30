#include "Muza/RT/Synth/Basic.h"

#include <stdlib.h>

void MzSynthBasicFreeSynthF(void * /*dataP*/, void *synthP) { free(synthP); }
