
#include "Muza/Blocks/Harmonizer.h"

#include "Muza/Blocks/Block.h"
#include "Muza/Functions/Numberers.h"
#include "Muza/Types.h"
#include "Muza/Wave.h"

MzHarmonizerZ MzHarmonizerG = {
    .blockM = &MzBlockG, .depthM = 7, .numbererM = MzNumberersSawF};

void MzHarmonizerCopyF(MzHarmonizerZ *harmonizerP, MzHarmonizerZ *fromP) {
  harmonizerP->blockM = fromP->blockM;
  harmonizerP->depthM = fromP->depthM;
  harmonizerP->numbererM = fromP->numbererM;
}

void MzHarmonizerWaveF(MzHarmonizerZ *harmonizerP, MzWaveZ *waveP) {
  MzBlockWaveF(harmonizerP->blockM, waveP);
  const MzFrequencyT frequencyL = MzBlockFrequencyF(harmonizerP->blockM);
  for (MzIndexT indexL = 2; indexL - 1 < harmonizerP->depthM; ++indexL) {
    MzIndexT numberL = harmonizerP->numbererM(indexL);
    MzBlockSetFrequencyF(harmonizerP->blockM,
                         frequencyL * (MzFrequencyT)numberL);
    MzWaveZ tmpL;
    MzBlockWaveF(harmonizerP->blockM, &tmpL);
    MzWaveAddF(waveP, &tmpL, 0.0, 1.0 / (MzAmplitudeT)numberL);
    MzWaveFreeF(&tmpL);
  }
  MzBlockSetFrequencyF(harmonizerP->blockM, frequencyL);
  MzWaveNormalizeF(waveP);
}

MzFrequencyT MzHarmonizerFrequencyF(MzHarmonizerZ *harmonizerP) {
  return MzBlockFrequencyF(harmonizerP->blockM);
}

void MzHarmonizerSetFrequencyF(MzHarmonizerZ *harmonizerP,
                               MzFrequencyT frequencyP) {
  MzBlockSetFrequencyF(harmonizerP->blockM, frequencyP);
}

void MzHarmonizerSetDurationF(MzHarmonizerZ *harmonizerP,
                              MzDurationT durationP) {
  MzBlockSetDurationF(harmonizerP->blockM, durationP);
}
