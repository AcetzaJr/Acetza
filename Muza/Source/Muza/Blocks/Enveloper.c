#include "Muza/Blocks/Enveloper.h"

#include "Muza/Blocks/Block.h"
#include "Muza/Blocks/Enveloper/Transform.h"
#include "Muza/Functions/Transformers.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzEnveloperZ MzEnveloperG = {.blockM = &MzBlockG,
                             .attackM = 1.0 / 16.0,
                             .holdM = 1.0 / 12.0,
                             .decayM = 1.0 / 8.0,
                             .sustainM = 1.0 / 2.0,
                             .releaseM = 1.0 / 4.0,
                             .attackTransformerM = MzTransformersSmoothF,
                             .decayTransformerM = MzTransformersSmoothF,
                             .releaseTransformerM = MzTransformersSmoothF};

void MzEnveloperCopyF(MzEnveloperZ *enveloperP, MzEnveloperZ *fromP) {
  enveloperP->blockM = fromP->blockM;
  enveloperP->attackM = fromP->attackM;
  enveloperP->holdM = fromP->holdM;
  enveloperP->decayM = fromP->decayM;
  enveloperP->sustainM = fromP->sustainM;
  enveloperP->releaseM = fromP->releaseM;
  enveloperP->attackTransformerM = fromP->attackTransformerM;
  enveloperP->decayTransformerM = fromP->decayTransformerM;
  enveloperP->releaseTransformerM = fromP->releaseTransformerM;
}

void MzEnveloperWaveF(MzEnveloperZ *enveloperP, MzWaveZ *waveP) {
  MzBlockWaveF(enveloperP->blockM, waveP);
  MzDurationT durationL = MzWaveDurationF(waveP);
  MzUntilZ untilL = MzUntilReleaseP(enveloperP, waveP, durationL);
  MzTransformF(waveP, enveloperP->releaseTransformerM, untilL.timeM,
               untilL.amplitudeM, durationL, 0.0, durationL);
}

MzFrequencyT MzEnveloperFrequencyF(MzEnveloperZ *enveloperP) {
  return MzBlockFrequencyF(enveloperP->blockM);
}

void MzEnveloperSetFrequencyF(MzEnveloperZ *enveloperP,
                              MzFrequencyT frequencyP) {
  MzBlockSetFrequencyF(enveloperP->blockM, frequencyP);
}

void MzEnveloperSetDurationF(MzEnveloperZ *enveloperP, MzDurationT durationP) {
  MzBlockSetDurationF(enveloperP->blockM, durationP);
}
